#pragma once

#define NTAB 32
#define IA 16807
#define IM 2147483647
#define IQ 127773
#define IR 2836
#define NDIV (1+(IM-1)/NTAB)
#define MAX_RANDOM_RANGE 0x7FFFFFFFUL

#define AM (1.0/IM)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

namespace Random
{
	int m_idum;
	int m_iy;
	int m_iv[NTAB];

	void SetSeed(int iSeed)
	{
		m_idum = ((iSeed < 0) ? iSeed : -iSeed);
		m_iy = 0;
	}

	int GenerateRandomNumber()
	{
		int j;
		int k;

		if (m_idum <= 0 || !m_iy)
		{
			if (-(m_idum) < 1)
				m_idum = 1;
			else
				m_idum = -(m_idum);

			for (j = NTAB + 7; j >= 0; j--)
			{
				k = (m_idum) / IQ;
				m_idum = IA * (m_idum - k * IQ) - IR * k;
				if (m_idum < 0)
					m_idum += IM;
				if (j < NTAB)
					m_iv[j] = m_idum;
			}
			m_iy = m_iv[0];
		}
		k = (m_idum) / IQ;
		m_idum = IA * (m_idum - k * IQ) - IR * k;
		if (m_idum < 0)
			m_idum += IM;
		j = m_iy / NDIV;

		// We're seeing some strange memory corruption in the contents of s_pUniformStream. 
		// Perhaps it's being caused by something writing past the end of this array? 
		// Bounds-check in release to see if that's the case.
		if (j >= NTAB || j < 0)
		{
			std::clog << "Warning: GenerateRandomNumber had an array overrun.\n";
			j = (j % NTAB) & 0x7fffffff;
		}

		m_iy = m_iv[j];
		m_iv[j] = m_idum;

		return m_iy;
	}

	float RandomFloat(float flLow, float flHigh)
	{
		// float in [0,1)
		float fl = AM * GenerateRandomNumber();
		if (fl > RNMX)
			fl = RNMX;

		return (fl * (flHigh - flLow)) + flLow; // float in [low,high)
	}

	float RandomFloatExp(float flMinVal, float flMaxVal, float flExponent)
	{
		// float in [0,1)
		float fl = AM * GenerateRandomNumber();
		if (fl > RNMX)
			fl = RNMX;

		if (flExponent != 1.0f)
			fl = powf(fl, flExponent);

		return (fl * (flMaxVal - flMinVal)) + flMinVal; // float in [low,high)
	}

	int RandomInt(int iLow, int iHigh)
	{
		unsigned int x = iHigh - iLow + 1;
		if (x <= 1 || MAX_RANDOM_RANGE < x - 1)
			return iLow;

		// The following maps a uniform distribution on the interval [0,MAX_RANDOM_RANGE]
		// to a smaller, client-specified range of [0,x-1] in a way that doesn't bias
		// the uniform distribution unfavorably. Even for a worst case x, the loop is
		// guaranteed to be taken no more than half the time, so for that worst case x,
		// the average number of times through the loop is 2. For cases where x is
		// much smaller than MAX_RANDOM_RANGE, the average number of times through the
		// loop is very close to 1.
		unsigned int maxAcceptable = MAX_RANDOM_RANGE - ((MAX_RANDOM_RANGE + 1) % x);
		unsigned int n;
		do
		{
			n = GenerateRandomNumber();
		} while (n > maxAcceptable);

		return iLow + (n % x);
	}
}