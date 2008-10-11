/**
  * ACM ICPC 2007 - Problem H "He is offside!" 
  * @author Alfredo Paz-Valderrama
  *
  */
import java.util.Scanner;
public class he{
   public static void main(String[] args){
      Scanner sc = new Scanner(System.in);
      int A = sc.nextInt();
      int D = sc.nextInt();
      while(A != 0 && D != 0){
         int minB = fMinC = sMinC = Integer.MAX_VALUE; 
         for(int i=0; i<A; i++){
            int B = sc.nextInt();
            minB = Math.min(minB, B);
         }
         for(int j=0; j<D; j++){
            int C = sc.nextInt();
            if( C < fMinC ){
               sMinC = fMinC;
               fMinC = C;
            }else 
               sMinC = Math.min(sMinC,C);
         }
         if(minB < sMinC) System.out.println("Y");
         else System.out.println("N");
         A = sc.nextInt();
         D = sc.nextInt();
      }
   }
}
