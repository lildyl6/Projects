package dylan;

import java.util.Scanner;

public class Bellaso {

	public static void main(String[] args) 
	{
		System.out.print("1 for encrypt, 2 for decrypt: ");
		
		
		Scanner scannerInit = new Scanner(System.in);
		int type = scannerInit.nextInt();
		
		
		System.out.print("message then key: ");
		
		Scanner scannerOne = new Scanner(System.in);
		Scanner scannerTwo = new Scanner(System.in);
		
		String message = scannerOne.nextLine();
		String key = scannerTwo.nextLine();

		if(type==1)
		{
			System.out.println(toBellaso(message,key));
		}
		else if(type==2)
		{
			System.out.println(fromBellaso(message,key));
		}
		else
		{
			System.out.println("Wrong!");
		}
	
	}
	
	public static String toBellaso(String plaintext, String keyword)
	{
		String output = "";
		String password = "";
		
		int j = 0;
		
		
		for(int i=0;i<plaintext.length();i++)
		{
			if(j>=keyword.length())
			{
				j-=keyword.length();
			}
			
			password+=keyword.charAt(j);
			j++;
		}
		
		plaintext = plaintext.toUpperCase();
		password = password.toUpperCase();
		
		
		for(int i=0;i<plaintext.length();i++)
		{
			char newChar = plaintext.charAt(i);
			char shift = password.charAt(i);
			int realShift =(int)(shift)-32;
			
			int next = (int)(newChar)+realShift;
			
			if(next>95)
			{
				next-=64;
			}
			output += (char)(next);
		}
		
		
		return output;

	}

	public static String fromBellaso(String ciphertext, String keyword)
	{
		String output = "";
		String password = "";
		
		int j = 0;
		
		
		for(int i=0;i<ciphertext.length();i++)
		{
			if(j>=keyword.length())
			{
				j-=keyword.length();
			}
			
			password+=keyword.charAt(j);
			j++;
		}
		
		ciphertext = ciphertext.toUpperCase();
		password = password.toUpperCase();
		
		
		for(int i=0;i<ciphertext.length();i++)
		{
			char newChar = ciphertext.charAt(i);
			char shift = password.charAt(i);
			int realShift = (int)(shift)-32;
			
			int next = (int)(newChar)-realShift;
			
			if(next<32)
			{
				next+=64;
			}
			output += (char)(next);
		}
		
		
		return output;
		
		
		
	}
	
}



