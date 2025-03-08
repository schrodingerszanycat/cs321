public class InputFile1 {

    public static void main(String[] args) {
        // Single-line comment: This is the main method where execution begins

        /*
         * Multi-line comment:
         * The following line prints a message to the console.
         * This is useful for testing the program's output.
         */
        System.out.println("Hello, World!");

        int number = 10; // This variable holds an integer value

        /*
         * Multi-line comment:
         * The following block of code checks if the number is even or odd.
         * If the number is even, it prints "Even Number".
         * Otherwise, it prints "Odd Number".
         */
        if (number % 2 == 0) {
            System.out.println(number + " is an Even Number");
        } else {
            System.out.println(number + " is an Odd Number");
        }
    }
}