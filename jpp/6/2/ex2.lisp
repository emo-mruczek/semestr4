(defun binomial (n k)
    (cond ((= k 0) 1) ((= n k) 1) (t (+ (binomial (- n 1) k) (binomial (- n 1) (- k 1))))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


(defun next-row (row)
  (mapcar #'+ (append row '(0)) (append '(0) row)))

(defun generate-pascal-row (n current-row)
  (if (= n 0)
      current-row
      (generate-pascal-row (- n 1) (next-row current-row))))

(defun generate-pascal (n)
  (generate-pascal-row n '(1)))

(defun binomial2 (n k)
  (nth k (generate-pascal n)))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun small (list)
  (or (null list) (null (cdr list))))

(defun right-half (list)
  (last list (ceiling (/ (length list) 2))))
(defun left-half (list)
  (ldiff list (right-half list)))

(defun mergelists (list1 list2)
  (merge 'list list1 list2 #'<))
(defun mergesort (list)
  (if (small list) list
	  (mergelists
		(mergesort (left-half list))
		(mergesort (right-half list)))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun gcde (a b)
  (if (= a 0)
      (values b 0 1)
      (multiple-value-bind (g x y)
          (gcde (mod b a) a)
        (values g (- y (* (floor b a) x)) x))))

(defun de (a b)
  (multiple-value-bind (x y g)
      (gcde a b)
    (values x y g)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun factorize (n factor)
  (cond
    ((= 1 n) nil)
    ((= 0 (mod n factor)) (cons factor (factorize (/ n factor) factor)))
    (t (factorize n (+ factor 1)))))


(defun prime-factors (n)
  (factorize n 2))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun gcdi (a b)
  (if (= a 0) b
      (gcdi (mod b a) a)))

(defun is-coprime (a b)
  (= (gcdi a b) 1))

(defun totient-helper (n i)
  (cond ((= i n) (if (is-coprime n i) 1 0))
        ((is-coprime n i) (1+ (totient-helper n (1+ i))))
        (t (totient-helper n (1+ i)))))

(defun totient (n)
  (totient-helper n 1))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun totient2 (n)
  (let ((unique-factors (remove-duplicates (prime-factors n))))
    (reduce #'(lambda (acc p) (floor (/ (* acc (- p 1)) p))) unique-factors :initial-value n)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


(defun prime? (n &optional (divisor 2))
  (cond ((<= n 1) nil)
        ((= n 2) t)
        ((evenp n) nil)
        ((> divisor (isqrt n)) t)
        ((zerop (mod n divisor)) nil)
        (t (prime? n (+ divisor 1)))))

(defun primes-helper (n result)
  (if (zerop n)
      result
      (if (prime? n)
          (primes-helper (- n 1) (cons n result))
          (primes-helper (- n 1) result))))

(defun primes (n)
  (primes-helper n '()))

