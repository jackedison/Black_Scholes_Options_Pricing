<h1> Options Calculations in C++ </h1>

* Option pricing using Black-Scholes
* Implied volatility calc

<h3> Black-Scholes </h3>

The Blach-Scholes option pricing model provides a closed-form pricing formula for a European type option.

There is no closed-form inverse for it (unsure why, perhaps distributions?).


<h3> Implied Volatility </h3>

Implied volatility is a calculation that uses an option's Vega (its sensitivity to change in volatility) to derive an estimate of volatility.

There is no closed-form inverse to the Black Scholes formula, however, it has a closed-form vega (volatility derivative) closed-form solution with a nonnegative derivative.

Therefore, we can use the Newton-Raphson formula to compute IV.

σn+1=σn−BS(σn)−Pν(σn)

$k_n^2$

k_n^2




<h3> Normal distribution functions (pdf and cdf; probability density and cumulative density functions) </h3>

![Distribution functions](img/distribution_functions.png)


<h3> What else to include? </h3>

* Max loss
* Max return
* Profit probability
* SMILE curve?
* Theta decay?
* Interactive interface?

* Could add a header file to define class and functions but unecessary for now. If multiple uses/implementations then maybe


<h3> Useful reference links </h3>

* https://goodcalculators.com/black-scholes-calculator/
* https://github.com/EsterHlav/Black-Scholes-Option-Pricing-Model (Java implementation useful - Geometric Brownian Motion)
