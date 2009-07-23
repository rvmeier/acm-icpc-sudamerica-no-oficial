import java.util.Scanner;
/**
 * @author Alfredo Paz-Valderrama
 *
 */
public class lottery {
	public static void main(String[] args) {
		int N,C,K;
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		C = sc.nextInt();
		K = sc.nextInt();
		while (!(N == 0 && C == 0 && K == 0)){
			int [] cont = new int[K];
			int min = Integer.MAX_VALUE;
			while(N>0){
				int c=C;
				while(c>0){
					int x = sc.nextInt();
					cont[x-1]++;
					c--;
				}
				N--;
			}
			for (int i : cont)
				min = Math.min(min, i);
                        int i ;
			for(i = 0;i < cont.length; i++)
				if (cont[i]==min) {
					System.out.print((i + 1));
                                        break;
                                }
                        for(;i < cont.length; i++)
				if (cont[i]==min) {
					System.out.print(" "+(i + 1));
                                        break;
                                }
			System.out.println();
			N = sc.nextInt();
			C = sc.nextInt();
			K = sc.nextInt();
		}
	}

}
