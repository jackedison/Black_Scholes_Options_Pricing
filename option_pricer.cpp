// Take in option parameters and compute implied volatility using Black Scholes

#include <iostream>
#include <cmath>  // pre-processor directive to include header file of cmath
#include <random>

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
        return cdf_n(d1()) * s - cdf_n(d2()) * k * pow(exp(1), -r * t);
    }

    double put_price()
    {
        // Returns: Put price in $
        return k * pow(exp(1), -r * t) * cdf_n(-d2()) - s * pow(exp(1), -d * t) * cdf_n(-d1());
    }

    double implied_volatility_trial_and_error(double market_price, double degrees = 4)
    {
        // Trivial trial and error solution to find implied volatility
        double v_try = 0;  // first volatility to try
        double increment = 1 / pow(10, degrees);  // amount to increement by

        // Iterate through option objects, trying next volatility until price is close
        Option next_option(s, k, r, t, v_try, d);
        double next_price = next_option.call_price();

        while ((next_price < market_price) & (v_try < 3))
        {
            v_try += increment;  // add 0.1% to volatility and try again
            Option next_option(s, k, r, t, v_try, d);
            next_price = next_option.call_price();
        }
        return v_try;
    }

    double implied_volatility(double market_price)
    {
        double next_iv = sqrt((2 * M_PI) / t) * (call_price() / s);
        cout << "Starting IV estimate: " << next_iv << endl;

        for (int i = 1; i < 10; i++){
            Option next_option(s, k, r, t, next_iv, d);
            next_iv = next_option.v - ((next_option.call_price() - next_option.k) / next_option.vega());
            cout << "Next IV estimate: " << next_iv << endl;

        }
        cout << "Final IV estimate: " << next_iv << endl;
        return next_iv;
    }

    double vega()
    {
        /* delta call price / delta volatility
        i.e. how much call price changes when volatility changes
        In what direction and to what extend the call price will move if there is a positive 1% change in volatility
        */
       return s * sqrt(t) * pdf_n(d1());
    }



    // Access specifier for private variables and member functions
    private:
        double d1()
        {
            return (log(s/k) + (r + pow(v, 2)/2) * t) / (v * sqrt(t));
        }

        double d2()
        {
            return d1() - v * sqrt(t);
        }

        double pdf_n(double x, double u = 0, double sig = 1)
        {
            /* Probability density function of the variable x on normal distribution. See:
            https://en.wikipedia.org/wiki/Normal_distribution
            https://support.microsoft.com/en-us/office/norm-dist-function-edb1cc14-a21c-4e53-839d-8082074c9f8d
            */
            return (1 / (sig * sqrt(2 * M_PI))) * pow(exp(1), -0.5 * pow(((x - u) / sig), 2));
        }

        double cdf_n(double x)
        { 
            /* CDF of the normal distribution; Phi(-∞, x) aka N(x)
            i.e. if normally distributed, what % does x standard deviations cover. So 0 standard deviations = 50% (below mean). 1std = 84.13%, -1std = 15.87%. 1.96std = 97.5% 
            Also the integral of the above from negative infinity to x (area under the curve)
            */
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
    cout << "Vega: " << option.vega() << endl;
    option.implied_volatility(100);
    cout << "Implied vol trial and error: " << option.implied_volatility_trial_and_error(100) << endl;


    return 1;
}





