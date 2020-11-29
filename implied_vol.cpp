// Take in option parameters and compute implied volatility using Black Scholes

#include <iostream>
#include <cmath>

using namespace std;

class Option
{
    // Access specifier for public variables and member functions (can also have protected and private)
    public:
      double s, k, r, t, v, d;

    // Parametrised Constructor (default one can be without variables if allowed). Always public and no return value.
    Option(double spot_price, double strike_price, double risk_free_rate, double time_to_expiration, double volatility, double dividend_yield = 0)
    {
        // Parameters: s Stock Price, k Strike price, r Risk free rate, t Time to maturity (years), v Volatility, d Dividend yield = 0
        s = spot_price;
        k = strike_price;
        r = risk_free_rate;
        t = time_to_expiration;
        v = volatility;
        d = dividend_yield;
    }

    double call_price()
    {
        // Returns: Call price in $
        return n(d1()) * s - n(d2()) * k * pow(exp(1), -r * t);
    }

    double put_price()
    {
        // Returns: Put price in $
        return k * pow(exp(1), -r * t) * n(-d2()) - s * pow(exp(1), -d * t) * n(-d1());
    }

    void print()
    {
        cout << d2() << endl;
    }

    // Access specifier for private variables and member functions
    private:
        double d1()
        {
            return (log(s/k) + (r + pow(v, 2)/2) * t) / (v * sqrt(t));
        }

        double d2()
        {
            double d2 = d1() - v * sqrt(t);
            return d2;
        }

        double n(double x)
        { 
            /* CDF of the normal distribution; Phi(-∞, x) aka N(x)
            i.e. if normally distributed, what % does x standard deviations cover. So 0 standard deviations = 50% (below mean). 1std = 84.13%, -1std = 15.87%. 1.96std = 97.5% */
            return erfc(-x/sqrt(2))/2;
        }
};

int main(){
    // Input parameters
    double spot_price = 300;
    double strike_price = 250;
    double risk_free_rate = 0.03;
    double time_to_expiration = 1;
    double dividend_yield = 0;
    double volatility = 0.15;  // to calculate theoretical, if not will compute IV

    // Black-Scholes calculations
    Option option(spot_price, strike_price, risk_free_rate, time_to_expiration, volatility, dividend_yield);
    cout << "Call price: $" << option.call_price() << endl;
    cout << "Put price: $" << option.put_price() << endl;

    return 1;
}





