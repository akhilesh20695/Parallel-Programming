args <- commandArgs(trailingOnly = TRUE)
print(args)

#Getting the arguments from command line
S0<-as.numeric(args[1])
mu<-as.numeric(args[2])
sigma<-as.numeric(args[3])
time<-as.numeric(args[4])
simulations<-as.numeric(args[5])

#dt=time interval
dt<-time/(simulations-1)
#timeline for graph plotting
timeline<-seq(0,time,dt)
#declaring an array for stock prices
s<-rep(0,times=simulations)
#initializing it with initial stock proce
s[1]<-S0
#declaring an array for storing norma random varibales
f<-rep(0,simulations)

#performing simulations
for(i in 2:simulations)
{
  #generating a normal random varibale and storing it's cumulative sum
  f[i]<-f[i-1]+sqrt(dt)*rnorm(1)
  #calculating the stock prices
  s[i]<-S0*exp((mu-(sigma^2)*0.5)*(i-1)*dt + sigma*f[i])
}
#declaring range for graph purposes
o_range<-range(s)

#plotting brownian motion graph
plot(timeline,s, ylim=o_range, type="l", col="coral1")
title(main="Geometric Brownian Motion Stock Price Movement", col.main="red", font.main=4)
