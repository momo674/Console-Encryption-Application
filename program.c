#include <stdio.h>
#include <string.h>
#define MAX_BUF  256
#define IV 0b11001011

unsigned char initKey();
unsigned char processKey(unsigned char);

void encode(unsigned char*, unsigned char*, unsigned char, int);
void decode(unsigned char*, unsigned char*, unsigned char, int);

unsigned char encryptByte(unsigned char, unsigned char, unsigned char);
unsigned char decryptByte(unsigned char, unsigned char, unsigned char);
unsigned char cShiftRight(unsigned char);
unsigned char cShiftLeft(unsigned char);

int readBytes(unsigned char*, int);
unsigned char getBit(unsigned char, int);
unsigned char setBit(unsigned char, int);
unsigned char clearBit(unsigned char, int);

int main()
{
    char str[8];
    int  choice;

    printf("\nYou may:\n");
    printf("  (1) Encrypt a message \n");
    printf("  (2) Decrypt a message \n");
    printf("  (0) Exit\n");
    printf("\n  what is your selection: ");
    fgets(str, sizeof(str), stdin);
    sscanf(str, "%d", &choice);

    switch (choice) {

        case 1:
        {
            unsigned char plaintext[MAX_BUF];
            unsigned char partial_key = initKey();
            printf("  Please enter your message in plain text: ");
            int count = readBytes(plaintext, MAX_BUF);

            unsigned char ciphertext[count];
            
            encode(plaintext, ciphertext, partial_key, count);
            printf("  ");
            for (int i = 0; i < count; i++) {
                if (ciphertext[i] < 100) {
                }
                printf("%d ", ciphertext[i]);
                if (i == count - 1) {
                    printf("\n");
                }
            }

            for (int i = 0; i < 256; i ++) {
                plaintext[i] = 0;
            }

            break;
        }
        case 2:
        { 

            char input[256];
            unsigned char ciphertext[256];
            unsigned char partial_key = initKey();

            printf("  Enter ciphertext: ");
            int index = 0;
            while (fgets(input, sizeof(input), stdin) != NULL) {
                int number;
                char* token = strtok(input, " ");

                while (token != NULL) {
                    if (sscanf(token, "%d", &number) == 1) {
                        if (number == -1) {
                            goto done;
                        }
                        if (index < 256) {
                            ciphertext[index] = (unsigned char)number;
                            index++;
                        } else {
                            goto done;
                        }
                    }
                    token = strtok(NULL, " ");
                }
            }

        done:
            for (int i = index; i < 256; i++) {
                ciphertext[i] = 0; 
            }
            
            printf("\n");
            unsigned char plaintext[index];
            decode(ciphertext, plaintext, partial_key, index);
            for (int i = 0; i < index; i++) {
                printf("%c", plaintext[i]);
            }
            printf("\n");
            break;
        }
        case 0:
            printf("  Goodbye!\n");
            break;

        default:
            printf("  Sorry your input was not valid. Please try again. Goodbye!\n");

    }

    return 0;
}

/*
  Function:  readBytes
  Purpose:   Read bytes from standard input
       out:  buffer - The buffer to store the read bytes
       in:   max - The maximum capacity of the buffer
   return:   The number of bytes actually read from the user
*/
int readBytes(unsigned char* buffer, int max)
{
    int num = 0;
    fgets((char*)buffer, max, stdin);
    num = strlen((char*)buffer) - 1;
    buffer[num] = '\0';
    return num;
}

/*
  Function:  getBit
  Purpose:   Retrieve the value of a bit at a specified position in a byte
       in:   c - The byte from which a bit will be returned
       in:   n - The position of the bit to be returned
   return:   The value of the bit at position n in byte c (0 or 1)
*/
unsigned char getBit(unsigned char c, int n)
{
    return ((c & (1 << n)) >> n);
}

/*
  Function:  setBit
  Purpose:   Set a specified bit to 1 in a byte
       in:   c - The byte in which a bit will be set to 1
       in:   n - The position of the bit to be set to 1
   return:   The new value of the byte with bit n set to 1
*/
unsigned char setBit(unsigned char c, int n)
{
    unsigned char result;
    result = c | (1 << n);
    return result;
}

/*
  Function:  clearBit
  Purpose:   Set a specified bit to 0 in a byte
       in:   c - The byte in which a bit will be set to 0
       in:   n - The position of the bit to be set to 0
   return:   The new value of the byte with bit n set to 0
*/
unsigned char clearBit(unsigned char c, int n)
{
    unsigned char result;
    result = c & (~(1 << n));
    return result;
}

/*
  Function:  initKey
  Purpose:   Initialize the encryption key based on user input
   return:   The initialized encryption key
*/
unsigned char initKey()
{
    unsigned int input;
    while (1){
        printf("  Enter the partial key (between 1 and 15 inclusive): ");
        scanf(" %d", &input);
        fgetc(stdin);

        if (input >= 1 && input <= 15) {
            break;
        }
        else {
            printf("  ***Please enter a value between 1-15 (inclusive)***\n");
        }
    }

    unsigned char partial_key = (unsigned char) input;
    partial_key = partial_key << 4;

    for (int i = 7; i > 3; i--) {
        unsigned char bit = getBit(partial_key, i);
        int second_index = (i - 1) % 4;

        if (bit == 1) {
            partial_key = clearBit(partial_key, second_index);
        }
        else if (bit == 0) {
            partial_key = setBit(partial_key, second_index);
        }
    }
    return partial_key;
}

/*
  Function:  cShiftLeft
  Purpose:   Circular shift a byte to the left
       in:   byte - The byte to be shifted
   return:   The shifted byte
*/
unsigned char cShiftLeft(unsigned char byte)
{
    unsigned char updated;
    updated = (byte << 1) | (byte >> (8 - 1));
    return updated;
}

/*
  Function:  cShiftRight
  Purpose:   Circular shift a byte to the right
       in:   byte - The byte to be shifted
   return:   The shifted byte
*/
unsigned char cShiftRight(unsigned char byte)
{
    unsigned char updated;
    updated = (byte >> 1) | (byte << (8 - 1));
    return updated;
}

/*
  Function:  processKey
  Purpose:   Process the encryption key according to specific rules
       in:   key - The encryption key to be processed
   return:   The processed encryption key
*/
unsigned char processKey(unsigned char key) 
{
    if (key % 3 == 0) {
        for (int i = 0; i < 3; i ++) 
        {
            key = cShiftLeft(key);
        }
    }
    else {
        for (int i = 0; i < 2; i ++) 
        {
            key = cShiftLeft(key);
        }
    }
    return key;
}

/*
  Function:  encryptByte
  Purpose:   Encrypt a single byte using a given key and previous byte
       in:   pt - The byte to be encrypted
       in:   key - The encryption key
       in:   prev - The previous byte
   return:   The encrypted byte
*/
unsigned char encryptByte(unsigned char pt, unsigned char key, unsigned char prev) {
    unsigned char temp_byte = 0;
    for (int i = 0; i < 8; i++) {
        unsigned char key_bit = getBit(key, i);
        unsigned char pt_bit = getBit(pt, i);
        unsigned char prev_bit_second = getBit(prev, 7 - i);
        if (key_bit == 1) {
            prev = cShiftRight(prev);
            prev_bit_second = getBit(prev, 7 - i);
        }
        unsigned char result = pt_bit ^ prev_bit_second;
        if (result == 1) {
            temp_byte = setBit(temp_byte, i);
        }
        else if (result == 0) {
            temp_byte = clearBit(temp_byte, i);
        }
    }
    return temp_byte;
}

/*
  Function:  decryptByte
  Purpose:   Decrypt a single byte using a given key and previous byte
       in:   ct - The byte to be decrypted
       in:   key - The encryption key
       in:   prev - The previous byte
   return:   The decrypted byte
*/
unsigned char decryptByte(unsigned char ct, unsigned char key, unsigned char prev) {
    unsigned char temp_byte = 0;
    for (int i = 0; i < 8; i++) {
        unsigned char key_bit = getBit(key, i);
        unsigned char ct_bit = getBit(ct, i);
        unsigned char prev_bit_second = getBit(prev, 7 - i);
        if (key_bit == 1) {
            prev = cShiftRight(prev);
            prev_bit_second = getBit(prev, 7 - i);
        }
        unsigned char result = ct_bit ^ prev_bit_second;
        if (result == 1) {
            temp_byte = setBit(temp_byte, i);
        }
        else if (result == 0) {
            temp_byte = clearBit(temp_byte, i);
        }
    }
    return temp_byte;
}

/*
  Function:  encode
  Purpose:   Encode plaintext using a given key and store the result in ciphertext
       in:   pt - The plaintext to be encoded
       out:  ct - The resulting ciphertext
       in:   key - The encryption key
       in:   numBytes - The number of bytes to encode
*/
void encode(unsigned char *pt, unsigned char *ct, unsigned char key, int numBytes) {
    unsigned char updated_key = processKey(key);
    unsigned char prev;
    for (int i = 0; i < numBytes; i++) {
        if (i == 0) {
            prev = IV;
            ct[i] = encryptByte(pt[i], updated_key, IV);
        }
        else {
            prev = ct[i - 1];
            updated_key = processKey(updated_key);
            ct[i] = encryptByte(pt[i], updated_key, prev);
        }
    }
}

/*
  Function:  decode
  Purpose:   Decode ciphertext using a given key and store the result in plaintext
       in:   ct - The ciphertext to be decoded
       out:  pt - The resulting plaintext
       in:   key - The encryption key
       in:   numBytes - The number of bytes to decode
*/
void decode(unsigned char *ct, unsigned char *pt, unsigned char key, int numBytes) {
    unsigned char updated_key = processKey(key);
    unsigned char prev;
    for (int i = 0; i < numBytes; i++) {
        if (i == 0) {
            prev = IV;
            pt[i] = decryptByte(ct[i], updated_key, IV);
        }
        else {
            prev = ct[i - 1];
            updated_key = processKey(updated_key);
            pt[i] = decryptByte(ct[i], updated_key, prev);
        }
    } 
}
