import java.util.*;

/**
 * ACM ICPC 2007 - Problem C "Car Plates Competition" 
 * @author Alfredo Paz-Valderrama
 *
 * */
public class carplates{
   public static int diff(String s1, String s2){
      int resp=-10;
      if(isOld(s1) && isOld(s2))
         resp= minus(s1,s2,2);
      else if(!isOld(s1) && isOld(s2))
         resp = minus("ZZZ9999",s2,2)+minus(s1,"BBBBB00",4);
      else if(!isOld(s1) && !isOld(s2))
         resp = minus(s1,s2,4);
      return resp;
   }
   public static boolean cantPrint(char c){
      return c=='A' || c=='C'|| c=='M'|| c=='I'|| c=='P';
   }
   public static int minus(String s1, String s2, int b){
      char[] a1 = s1.toCharArray();
      char[] a2 = s2.toCharArray();
      String tmp = (b==4)?"BDEFGHJKLNOQRSTUVWXYZ":"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
      int resp=0, res=0, exp=1;
      for(int idx=6; idx>b; idx--){
         int n1 = a1[idx]-res;
         int n2 = a2[idx];
         int diff = n1 - n2;
         if(n1 >= n2){
            res = 0;
         }else{
            diff = 10 + diff;
            res = 1;
         }
         resp  = resp + diff*exp;
         exp = exp*10;
      }
      for(int idx=b; idx>=0; idx--){
         int n1 = tmp.indexOf(s1.substring(idx,idx+1))-res+1;
         int n2 = tmp.indexOf(s2.substring(idx,idx+1))+1;
         int diff = n1 - n2;
         if(n1 >= n2){
            res = 0;
         }else{
            diff = 10 + diff;
            res = 1;
         }
         resp  = resp + diff*exp;
         exp = exp*tmp.length();
      }
      if (res>0) resp = -1;
      return resp;
   }
   public static boolean isDigit(char c){
      return '0'<=c && c<='9';
   }
   public static boolean isAlpha(char c){
      return 'A'<=c && c<='Z';
   }
   public static boolean isOld(String s){
      return isDigit(s.charAt(3));
   }

   public static boolean isValid(String s){
      char[] a= s.toCharArray();
      if(isDigit(a[3])) {//is old
         for(int i=0; i<3; i++)
            if(!isAlpha(a[i])) return false;
         for(int i=3; i<7; i++)
            if(!isDigit(a[i])) return false;
      }else{ // is new
         for(int i=0; i<5; i++)
            if(!isAlpha(a[i]) || 
            		cantPrint(a[i])) 
            	return false;
         for(int i=5; i<7; i++)
            if(!isDigit(a[i])) return false;
      }
      return true;      
   }
   public static void main(String[] args){
      Scanner sc = new Scanner(System.in);
      String SM = sc.next();
      String SI = sc.next();
      int C = sc.nextInt();
      while(!SM.equals("*") || !SI.equals("*") || C!=0){
         if(!isValid(SI)) {
        	System.err.println("Invalid Si="+SI);
            System.out.println("N");
         }else{
            int d = diff(SI,SM);
            System.err.println("diff="+d);
            if(0<d && d <= C)
               System.out.println("Y");
            else
               System.out.println("N");
         }
         SM = sc.next();
         SI = sc.next();
         C = sc.nextInt();
      }
   }
}
