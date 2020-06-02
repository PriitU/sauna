# Sauna IoT

This is a small IoT hobby project that got started in April 2017.
The project involves a remote sensor setup using the [LoRa protocol](https://en.wikipedia.org/wiki/LoRa) to send data from a lakeside sauna (weather data and temperature in sauna) to a receiver node and a front- & backend setup to store and view the data.

Hardware:
Description of hardware setup (**TODO**). 
Image of setup (**TODO**).

Software:
V1 (2017-2019):
The initial version was built on the MERN stack (Mongodb, Express.js, React, Node.js) with the database hosted on [mLab](https://mlab.com/) and node server on [Heroku](https://www.heroku.com/).
Image of previous frontend (**TODO**).

V2 (2020-..):
In 2020 I rebuilt the system while learning AWS and decided to set it up as an [AWS serverless](https://aws.amazon.com/serverless/) solution with Dynamodb, API gateway and Lambda functions. The frontend this time was build with Vue.js.
Image of architecture (**TODO**).
Image of current frontend (**TODO**).

## This repository
This repo includes the Vue.js frontend, AWS Lambda functions for backend and Arduino code used on the IoT nodes handling the LoRa data exchange.
Image of previous architecture (**TODO**).
Code of previous setup (**TODO**).
