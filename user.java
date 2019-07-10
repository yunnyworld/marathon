//190606

package project;

import java.io.File;
import java.util.Scanner;


public class user
{
	String name;
	double record;
	int height;
	int weight;
	int age;
	char gender;
	public user(String name,double record, int height, int weight, int age, char gender)
	{
		this.name = name;
		this.record = record;
		this.height = height;
		this.weight = weight;
		this.age = age;
		this.gender = gender;
	}
	public void display()
	{
		System.out.println(this.name);
	}

	static int number_of_player;
	static int RET_SUCCESS = 0;
	static int RET_INVALID_GENDER = -1;
	static int RET_INVALID_AGE = -2;
	static int RET_INVALID_HEIGHT = -3;
	static int RET_INVALID_WEIGHT = -4;


	int user_create(user[] p)
	{
		try
		{
		File file = new File("userinfo.txt");
		Scanner scanfile = new Scanner(file);
		number_of_player = scanfile.nextInt();
		for(int i = 0;i<number_of_player;i++)
		{
			p[i].name = scanfile.next();
			p[i].record = scanfile.nextDouble();
			p[i].height = scanfile.nextInt();
			p[i].weight = scanfile.nextInt();
			p[i].age = scanfile.nextInt();
			p[i].gender = scanfile.next().charAt(0);
		}
		scanfile.close();
		}
		catch (Exception ex)
		{
			ex.printStackTrace();
		}
		return number_of_player;
	}

	public static int user_state(user[] p, int number)
	{
		System.out.println(p.length);
		System.out.println("Average is"+user_average(p,number));
		user first_player = user_first(p,number);
		System.out.println("First player is "+first_player.name+" and record of first player is "+first_player.record);
		System.out.println("Rate of Frank Rosendahl from total is "+user_rate(p,number,"Frank Rosendahl"));
		user_decgen(p,number,'f');
		user_decage(p,number,-20,-30);
		user_dechei(p,number,160,170);
		user_decwei(p,number,70,80);
		return RET_SUCCESS;
	}

	static double user_average(user[] p, int number)
	{
		double sum = 0;
		for(int i=0;i < number;i++)
		{
			sum += p[i].record;
		}
		double avg = sum/number;
		return avg;
	}

	static user user_first(user[] p,int number)
	{
		double min = p[0].record;
		int index = 0;
		for(int i =0;i< number;i++)
		{
			if(p[i].record < min)
			{
				index = i;
				min = p[i].record;
			}
		}
		return p[index]; //�ּҰ����� �ϸ� �ȵǳ�???
	}

	static double user_rate(user[] p, int number, String name)
	{
		int index = 0;
		double[] rankptr = new double[number];
		double[] rateptr = new double[number];
		for(int i=0;i < number;i++)
		{
			rankptr[i] = 1;
			if(!p[i].name.equals(name));
			{
				index = i;
			}
			for(int j = 0;j < number;j++)
			{
				if(p[i].record > p[j].record)
				{
					rankptr[i]++;
				}
			}
			rateptr[i] = rankptr[i]/number*100;
		}
		double return_value = rateptr[index];
		return return_value;
 	}

	static int user_decgen(user[] p, int number, char gender)
	{
		int cnt = 0;
		if((gender != 'm')&&(gender != 'f'))
		{
			System.out.println("Please check your age range.");
			return RET_INVALID_GENDER;
		}
		for(int i=0;i < number;i++)
		{
			if(p[i].gender == gender)
			{
				cnt++;
			}
		}
		user[] pgender = new user[cnt]; // �� player[cnt]�� �ؾ�����?

		int cntgender = 0;

		for(int i=0;i<number;i++)
		{
			if(p[i].gender == gender)
			{
				pgender[cntgender++] = p[i];
			}
		}


		System.out.println("pgender.length : "+pgender.length);


		System.out.println("Average of "+gender+" is "+user_average(pgender,cntgender));
		user first_player = user_first(pgender,cntgender);
		System.out.println("First player of"+gender+"is "+first_player.name+" and record of first player is "+first_player.record);
		return RET_SUCCESS;
		}


	static int user_decage(user[] p, int number, int a, int b)
	{
		int cnt = 0;
		if((a < 0)||(b < 0)||(b < a))
		{
			System.out.println("Please check your age range.");
			return RET_INVALID_AGE;
		}
		for(int i = 0; i < number; i++)
		{
			if((a <= p[i].age)&&(p[i].age < b))
			{
				cnt++;
			}
		}
		user[] page = new user[cnt];
		int cntage = 0;
		for(int i = 0; i < number; i++)
		{
			if((a <= p[i].age)&&(p[i].age < b))
			{
				page[cntage++] = p[i];
			}
		}
		System.out.println("Average of between "+a+"years old and "+b+"years old is "+user_average(page,cntage));
		user first_player = user_first(page,cntage);
		System.out.println("First player of between "+a+"years old and "+b+"years old is "+first_player.name+" and record of first player is "+first_player.record);
		return RET_SUCCESS;
	}

	static int user_dechei(user[] p, int number, int a, int b)
	{
		int cnt = 0;
		if((a < 0)||(b < 0)||(b < a))
		{
			System.out.println("Please check your height range.");
			return RET_INVALID_HEIGHT;
		}
		for(int i = 0; i < number; i++)
		{
			if((a <= p[i].height)&&(p[i].height < b))
			{
				cnt++;
			}
		}
		user[] phei = new user[cnt];
		int cnthei = 0;
		for(int i = 0; i < number; i++)
		{
			if((a <= p[i].height)&&(p[i].height < b))
			{
				phei[cnthei++] = p[i];
			}
		}
		System.out.println("Average of between "+a+"cm and "+b+"cm is "+user_average(phei,cnthei));
		user first_player = user_first(phei,cnthei);
		System.out.println("First player of between "+a+"cm and "+b+"cm is "+first_player.name+" and record of first player is "+first_player.record);
		return RET_SUCCESS;
	}

	static int user_decwei(user[] p, int number, int a, int b)
	{
		int cnt = 0;
		if((a < 0)||(b < 0)||(b < a))
		{
			System.out.println("Please check your weight range.");
			return RET_INVALID_WEIGHT;
		}
		for(int i = 0; i < number; i++)
		{
			if((a <= p[i].weight)&&(p[i].weight < b))
			{
				cnt++;
			}
		}
		user[] pwei = new user[cnt];
		int cntwei = 0;
		for(int i = 0; i < number; i++)
		{
			if((a <= p[i].weight)&&(p[i].weight < b))
			{
				pwei[cntwei++] = p[i];
			}
		}
		System.out.println("Average of between "+a+"kg and "+b+"kg is "+user_average(pwei,cntwei));
		user first_player = user_first(pwei,cntwei);
		System.out.println("First player of between "+a+"kg and "+b+"kg is "+first_player.name+" and record of first player is "+first_player.record);
		return RET_SUCCESS;
	}
}
