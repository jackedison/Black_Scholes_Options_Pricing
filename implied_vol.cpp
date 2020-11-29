// Take in option parameters and compute implied volatility using Black Scholes

#include <iostream>
#include <cmath>

using namespace std;

double calc_d1(double s, double k, double r, double t, double v, double d){
    double d1 = (log(s/k) + (r + pow(v, 2)/2) * t) / (v * sqrt(t));
    return d1;
}

double calc_d2(double d1, double t, double v){
    double d2 = d1 - v * sqrt(t);
    return d2;
}

double n(double x) { 
    /* CDF of the normal distribution; Phi(-∞, x) aka N(x)
    i.e. if normally distributed, what % does x standard deviations cover. So 0 standard deviations = 50% (below mean). 1std = 84.13%, -1std = 15.87%. 1.96std = 97.5% */
    return erfc(-x/sqrt(2))/2;
}

double call_price(double s, double k, double r, double t, double v, double d = 0){
    // Parameters: s Stock Price, k Strike price, r Risk free rate, t Time to maturity (years), v Volatility, d Dividend yield = 0
    // Returns: Call price in $
    double d1 = calc_d1(s, k, r, t, v, d);
    double d2 = calc_d2(d1, t, v);
    double call_px = n(d1) * s - n(d2) * k * pow(exp(1), -r * t);
    return call_px;
}

int main(){
    // Input parameters
    double spot_price = 300;
    double strike_price = 250;
    double risk_free_rate = 0.03;
    double time_to_expiration = 1;
    double dividend_yield = 0;
    double volatility = 0.15;  // to calculate theoretical, if not will compute IV

    // Black-Scholes calculations
    double call_px = call_price(spot_price, strike_price, risk_free_rate, time_to_expiration, volatility, dividend_yield);


    cout << "Call price: $" << call_px << endl;
    return 1;
}





