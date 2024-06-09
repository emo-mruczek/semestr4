fun binomial(n: int, k: int) = 
  if k = 0 then 1
  else if k = n then 1
  else binomial(n - 1, k) + binomial(n - 1, k - 1);

(******************************************************)

fun next_row([]) = []
  | next_row([x]) = []
  | next_row(x::y::rest) = (x + y) :: next_row(y::rest)

fun pascal_row(0) = [1]
  | pascal_row(n) =
      let
        val prev_row = pascal_row(n-1)
      in
        1 :: next_row(prev_row) @ [1]
      end

fun binomial2(n, k) =
  let
    val row = pascal_row(n)
  in
    List.nth(row, k)
  end

(***********************************************************)

	fun listOfLists nil = nil 
	| listOfLists (f::e) = [f]::listOfLists(e);

	fun merge(xs,nil) = xs
	| merge(nil,ys) = ys
	| merge(x::xs, y::ys) =
	if (x < y) then x::merge(xs, y::ys) else y::merge(x::xs,ys);
	

	fun mergePass [] = []
	| mergePass (x::nil) = [x]
	| mergePass (i::j::k) = if (length (i::j::k)) < 1 then mergePass(i::j::k) else [merge(i,j)]@mergePass(List.drop((i::j::k),2));
	
	fun mergeSortCon [] = []
	| mergeSortCon (x::nil) = x
	| mergeSortCon (x::y::z) = mergeSortCon((mergePass(x::y::nil))@(mergePass(z)));

	fun mergeSort [] = [] 
	| mergeSort (x) = mergeSortCon (listOfLists(x)); 

(*************************************************************)

fun gcde 0 b = (b, 0, 1)
  | gcde a b =
    let
      val (g, x, y) = gcde (b mod a) a
    in
      (g, y - (b div a) * x, x)
    end

fun de a b =
  let 
    val (g, x, y) = gcde a b
  in
    (x, y, g)
  end

(************************************************************)

fun primeFactors n = 
    let
        fun factorize 1 _ = []
          | factorize n factor =
              if n mod factor = 0 then
                  factor :: factorize (n div factor) factor
              else
                  factorize n (factor + 1)
    in
        factorize n 2
    end

(*************************************************************)

fun gcdi 0 b = b
  | gcdi a b = gcdi (b mod a) a

fun is_coprime (a, b) = (gcdi a b) = 1

fun totient n = 
    let
        fun filter_coprime [] = []
          | filter_coprime (x::xs) = if is_coprime (n, x) then x :: filter_coprime xs else filter_coprime xs
    in
        List.length (filter_coprime (List.tabulate (n, fn x => x + 1)))
    end


(**************************************************************)

fun intPow (x, 0) = 1
  | intPow (x, n) = x * intPow (x, n - 1)

fun group [] = []
  | group (x::xs) = 
    let
        val (prefix, suffix) = List.partition (fn y => y = x) xs
    in
        (x::prefix) :: group suffix
    end

fun totient2 n =
    let
        fun product (p, k) = (p - 1) * intPow (p, k - 1)
        val factors = primeFactors n
        val groupedFactors = group factors
        val factorCounts = List.map (fn xs => (List.hd xs, List.length xs)) groupedFactors
    in
        List.foldl (fn (pk, acc) => acc * product pk) 1 factorCounts
    end

(****************************************************************)

fun createList(ending) =
  let 
    fun createListX(start, ending) =
      if start = ending then []
      else start :: createListX(start + 1, ending)
  in
    createListX(1, ending + 1)
  end;

fun removeMult ([], n) = []
  | removeMult (x::xs, n) = 
      if x mod n = 0 then 
        removeMult(xs, n)
      else 
        x :: removeMult(xs, n);

fun sieveN([], primes) = primes
  | sieveN(1::ns, primes) = sieveN(ns, 1 :: primes)
  | sieveN(n::ns, primes) = sieveN(removeMult(ns, n), n :: primes);

fun sieve(n) = sieveN(createList(n-1), []);
