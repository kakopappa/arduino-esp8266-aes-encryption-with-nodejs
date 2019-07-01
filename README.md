# arduino-esp8266-aes-encryption-with-nodejs

This repo demostrates how to encypt your data using [AES](https://github.com/spaniakos/AES) and decrypt it using NodeJS crypto-js library. If you are looking for PHP port see https://zeitwesentech.com/blog/?p=521 (I am not the author)


You can find the library version here
https://github.com/kakopappa/arduino-esp8266-aes-lib

Complete article is here: (I am not the author)
https://primalcortex.wordpress.com/2016/06/17/esp8266-logging-data-in-a-backend-aes-and-crypto-js/. 

I have fixed few bugs related ESP8266 and combined it with AES and Base64

How to use this:

1. Clone the github repo.
2. open aes_encryption.ino in Arduino
3. Flash

![conole output](https://github.com/kakopappa/arduino-esp8266-aes-encryption-with-nodejs/blob/master/iv-5-snap.png "Console")


4. Copy the iv, encrypted data and replace the esp8266_msg, esp8266_iv in the javascript code below.



Here is the NodeJS Code.

```javascript
//npm install --save-dev crypto-js
var CryptoJS = require("crypto-js");
var esp8266_msg = 'IqszviDrXw5juapvVrQ2Eh/H3TqBsPkSOYY25hOQzJck+ZWIg2QsgBqYQv6lWHcdOclvVLOSOouk3PmGfIXv//cURM8UBJkKF83fPawwuxg=';
var esp8266_iv  = 'Cqkbb7OxPGoXhk70DjGYjw==';

// The AES encryption/decryption key to be used.
var AESKey = '2B7E151628AED2A6ABF7158809CF4F3C';

var plain_iv =  new Buffer( esp8266_iv , 'base64').toString('hex');
var iv = CryptoJS.enc.Hex.parse( plain_iv );
var key= CryptoJS.enc.Hex.parse( AESKey );

console.log("Let's ");

// Decrypt
var bytes  = CryptoJS.AES.decrypt( esp8266_msg, key , { iv: iv} );
var plaintext = bytes.toString(CryptoJS.enc.Base64);
var decoded_b64msg =  new Buffer(plaintext , 'base64').toString('ascii');
var decoded_msg =     new Buffer( decoded_b64msg , 'base64').toString('ascii');

console.log("Decryptedage: ", decoded_msg);
```


