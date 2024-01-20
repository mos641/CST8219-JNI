import java.util.Random;
import java.util.Scanner;

public class JavaMenu {

	static { System.loadLibrary("MyCPPLibrary"); }

	public static void main(String[] args) {
		// object of this class
		JavaMenu obj = new JavaMenu();
		
		// array for numbers
		int[] numbers;
		// int for user input
		int userInput = -1;
		Scanner input = new Scanner(System.in);
		Random random = new Random();
		double stdDev;
		double mean;
		
		// loop to ask for user input
		while(userInput == -1) {
			// ask for input
			System.out.print("Enter the number of samples to generate: ");
			
			// if its an int store it
			if (input.hasNextInt()) {
				userInput = input.nextInt();
			}
			
			// check it is greater than 0
			if (userInput <= 0) {
				userInput = -1;
				System.out.println("Number must be a whole number greater than 0, try again.");
			}
		}
		
		// loop to generate random numbers
		numbers = new int[userInput];
		for(int i = 0; i < userInput; i++) {
			// store random int
			numbers[i] = random.nextInt(100);
		}
		
		// invoke the cpp functions, passing our array through and timing the calculations
		long timeBefore = System.currentTimeMillis();
		stdDev = obj.calculateSTDDev(numbers);
		mean = obj.calculateMean(numbers);
		long timeAfter = System.currentTimeMillis();
		
		// print the results
		System.out.println("The standard deviation is " + stdDev + ", the mean is " + mean);
		System.out.println("It took " + (timeAfter - timeBefore) + " milliseconds to calculcate");
		
		input.close();
	}
	
	// cpp functions
	public native double calculateSTDDev( int [] numbers );
	public native double calculateMean(int [] numbers );

}