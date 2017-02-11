#include "AES.h"
#include "base64.h"

AES aes;

uint8_t getrnd() {
    uint8_t really_random = *(volatile uint8_t *)0x3FF20E44;
    return really_random;
}

// Generate a random initialization vector
void gen_iv(byte  *iv) {
    for (int i = 0 ; i < N_BLOCK ; i++ ) {
        iv[i]= (byte) getrnd();
    }
}
    
void setup() {
    Serial.begin(115200);
    Serial.println("\nBooting...");  

    char b64data[200];
    byte cipher[1000];
    byte iv [N_BLOCK] ;
    
    Serial.println("Let's encrypt:");
    // Our AES key. Note that is the same that is used on the Node-Js side but as hex bytes.
    byte key[] = { 0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C };
    
    // The unitialized Initialization vector
    byte my_iv[N_BLOCK] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    
    // Our message to encrypt. Static for this example.
    String msg = "{\"data\":{\"value\":300}, \"SEQN\":700 , \"msg\":\"IT WORKS!!\" }";
    
    aes.set_key( key , sizeof(key));  // Get the globally defined key
    gen_iv( my_iv );                  // Generate a random IV
    
    // Print the IV
    base64_encode( b64data, (char *)my_iv, N_BLOCK);
    Serial.println(" IV b64: " + String(b64data));

    Serial.println(" Message: " + msg );
 
    int b64len = base64_encode(b64data, (char *)msg.c_str(),msg.length());
    Serial.println (" Message in B64: " + String(b64data) );
    Serial.println (" The lenght is:  " + String(b64len) );
    
    // For sanity check purpose
    //base64_decode( decoded , b64data , b64len );
    //Serial.println("Decoded: " + String(decoded));
    
    // Encrypt! With AES128, our key and IV, CBC and pkcs7 padding    
    aes.do_aes_encrypt((byte *)b64data, b64len , cipher, key, 128, my_iv);
    
    Serial.println("Encryption done!");
    
    Serial.println("Cipher size: " + String(aes.get_size()));
    
    base64_encode(b64data, (char *)cipher, aes.get_size() );
    Serial.println ("Encrypted data in base64: " + String(b64data) );
      
    Serial.println("Done...");
}

void loop() {
  // put your main code here, to run repeatedly:

}
