public class GenerateTimeStamps {
	

	public static void main (String [] args){

		for (int i = 1734; i < 3277; i+=5){

			

			if (i%60 < 10){
				System.out.println ("03/06/16-20:"+i/60+":0"+i%60+" = 16.71");
			}
			else {
				System.out.println ("03/06/16-20:"+i/60+":"+i%60+" = 16.71");
			}
		}

	}
}

