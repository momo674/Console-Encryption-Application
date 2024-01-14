I developed a comprehensive software program in accordance with the provided instructions. The program initiates by prompting the user to specify their preference, whether it be encrypting a readable message (plaintext) or decrypting an already encrypted sequence of numbers (ciphertext).

The encryption algorithm, as outlined in the specifications, was meticulously implemented to ensure clarity and effectiveness. This algorithm securely transforms plaintext into ciphertext. Additionally, a corresponding decryption algorithm was deduced and implemented to reverse the process, converting the ciphertext back into its original readable form.

To maintain a structured and modular codebase, the software was organized into separate functions, each serving a distinct purpose and contributing to the overall functionality of the program. This approach aligns with the programming conventions covered in the course lectures, ensuring a clear and maintainable code structure.

To enhance the robustness of the program, basic error checking mechanisms were incorporated. These mechanisms identify and handle potential issues arising from user input or during program execution, providing informative error messages to guide users through any incorrect inputs or unexpected situations.

Every function in the code was extensively documented, following a consistent and clear documentation style. This documentation outlines the purpose of each function, specifies input parameters, and describes the expected output. This meticulous documentation contributes to the code's readability and facilitates future maintenance.

Adherence to the programming conventions, such as naming conventions, indentation, and code commenting, was prioritized throughout the development process. This ensures that the resulting codebase is not only functional but also adheres to best practices for code organization and presentation.

Lastly, any additional constraints mentioned in the Constraints section of the document were considered during the development process. The program was designed to meet all specified requirements and constraints, providing a robust and user-friendly solution for encrypting and decrypting messages.

PURPOSE: Create an ecryption algorithm using specific keys asociated with ascii and bit values.
SOURCE FILES: program.c
LAUNCH INSTRUCTIONS: 1. open terminal and located this folder `COMP2401_A2` and run the command `gcc a2.c`
                     2. then run the a.out file by entering ./a.out in terminal
                     3. Either create a message to encrypt (prompt 1), decrypt an existing encrypted method (prompt 2), or exit (prompt 3)
