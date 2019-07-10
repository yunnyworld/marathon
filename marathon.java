//190606

package project;

import java.io.File;
import java.util.Scanner;

//import project.user.*;

public class marathon {

	static String DEFAULT_FILE  = "userinfo.txt";

	public static void main(String[] args) {
		{
			  String datafile;

			  if(args.length == 1)
			  {
			    datafile = DEFAULT_FILE;
			  } else if(args.length == 2)
			  {
			    datafile = args[1];
			  } else if(args.length >2)
			  {
			    System.out.println("Usage: ./marathon datafile");
			    System.exit(0);
			  }


					try
					{
					String path = marathon.class.getResource("").getPath();
					File file = new File(path + "userinfo.txt");
					Scanner scanfile = new Scanner(file);
					int number = scanfile.nextInt();
					user[] p = new user[number];
					for(int i = 0;i<number;i++)
					{
						String name = scanfile.next();
						double record = scanfile.nextDouble();
						int height = scanfile.nextInt();
						int weight = scanfile.nextInt();
						int age = scanfile.nextInt();
						char gender = scanfile.next().charAt(0);
						p[i] = new user(name,record,height,weight,age,gender);
						p[i].display();
					}
					user.user_state(p, number);
					scanfile.close();
					}
					catch (Exception ex)
					{
						ex.printStackTrace();
					}
				}



			  return;
			}
	}
