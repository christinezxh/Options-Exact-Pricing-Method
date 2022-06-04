# Options-Exact-Pricing-Method
## Background Concepts

#### Unlike most American Options, European options (with zero dividends) price and sensitivities (delta, gamma, vegas...) could be calculated using the exact formula. These options can be exercised at the expiry time T only, so no early exercise are allowed.

### Exact Option Pricing (Black-Scholes Model)
#### The Black-Scholes call option formula is calculated by multiplying the stock price by the cumulative standard normal probability distribution function. Thereafter, the net present value (NPV) of the strike price multiplied by the cumulative standard normal distribution is subtracted from the resulting value of the previous calculation. (from investopedia.com)

#### Here is the exact formula for option call price (note that C indicates call price, and P indicates put price in this project):
#### C = Se^(b-r)T * N(d1) - Ke^-rT * N(d2)
#### P = Ke^-rT * N(-d2) -Se^(b-r)T * N(-d1)
#### S = asset price, K = strike price, T = exercise(maturity) date, r = risk-free interest rate, σ = constant volatility, b = cost of carry
#### relationship between Call Price and Put Price (I do have a method to prove the relationship is valid in the codes, please refer to IsEuropeanPutCallParity() in EuropeanOption class)
#### C + Ke^-rT = P + S

### Options Sensitivities (the Greeks)
#### Option Greeks measures how an option's price wil react to change in the underlying stock price(s), time to expiration(T), and impiled volatility(σ) 
#### generally speaking, greeks is very useful to help investors to choose the options
### Perpetual American Options Exact Pricing

#### Although most American options can be exercised before the expiry date (and usually would be the case, because the time value will goes to 0 as closer to the exercise date), there is one exception known as Perpetual American Options. There's an exact solution applying to this option.
#### The formulae are:
#### C = K/(y1-1) * ((y1-1)/y1 * S/K) ^y1
#### y1 = 1/2 - b/σ^2 + ((b/σ^2 - 1/2)^2 + 2r/σ^2)^1/2
#### P = K/(1-y2) * ((y2-1)/y2 * S/K) ^y2
#### y2 = 1/2 - b/σ^2 - ((b/σ^2 - 1/2)^2 + 2r/σ^2)^1/2
#### notice that T would not be considered in American options
