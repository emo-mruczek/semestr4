
using System;

public class DHSetup<T> where T: GF, new()
{
   private T generator;
   
   private T generateGenerator(T dum)
   {
      Random random = new Random();
      int max = (int)dum.GetCharacteristic();
      int number = random.Next(1, max - 1);
      return (T) new GF (number);
   }

   public DHSetup(T dum)
   {
      this.generator = generateGenerator(dum);
   }

   public T getGenerator()
   {
      return generator;
   }
   
   public T power(T a, ulong b) {
      if (b == 0) {
         return (T) new GF (1);
      }
      T temp = power(a, b/2);
      if (b % 2 == 0) {
         return (T) (temp * temp);  
      } else {
         return (T) (a*temp*temp);
      }
    
   }
}
