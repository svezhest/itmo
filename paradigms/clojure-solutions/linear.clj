(defn everyInSec? [pred, vs]
  {:pre  [(coll? vs)]
   :post [(boolean? %)]}
; :NOTE: every?
  (reduce (fn [a, b] (and a (pred b))) true vs))

(defn equalInSec? [f]
  (fn [vs]
    {:pre  [(coll? vs)]
     :post [(boolean? %)]}
    (apply == (mapv f vs))))

(def equalSize? (equalInSec? count))
(def equalType? (equalInSec? type))

(defn isVector? [v]
      (and (vector? v) (everyInSec? number? v)))

(defn coordOperation [f checker]
  (fn [& vs]
    {:pre  [(every? vector? vs) (equalSize? vs) (everyInSec? checker vs)]
     :post [(vector? %) (equalSize? (vector % (first vs))) (checker %)]}
    (apply mapv f vs)))

; :NOTE: Копипаста
(def v+ (coordOperation + isVector?))
(def v- (coordOperation - isVector?))
(def v* (coordOperation * isVector?))

; :NOTE: Число столбцов
(defn matrix? [m]
  {:pre  [true]
   :post [(boolean? %)]}
  (and (vector? m) (every? vector? m) (equalSize? m)))

(defn tensor? [vs]
  {:pre  [(coll? vs) (or (every? number? vs) (every? vector? vs))]
   :post [(boolean? %)]}
  (if (number? (first vs)) true (and (equalSize? vs) (and (tensor? (map first vs)) (every? tensor? vs)))))

(def m+ (coordOperation v+ matrix?))
(def m- (coordOperation v- matrix?))
(def m* (coordOperation v* matrix?))

(defn scalar [a, b]
  {:pre  [(vector? a) (vector? b) (equalSize? (vector a, b))]
   :post [(number? %)]}
  (apply + (v* a b)))


(defn vect [& vs]
  {:pre  [(every? vector? vs)]
   :post [(vector? %) (== 3 (count %))]}
  (reduce (fn [a b]
            {:pre  [(vector? a) (vector? b) (== (count a) (count b) 3)]
             :post [(vector? %) (== 3 (count %))]}
            [(- (* (nth a 1) (nth b 2)) (* (nth a 2) (nth b 1)))
             (- (* (nth a 2) (nth b 0)) (* (nth a 0) (nth b 2)))
             (- (* (nth a 0) (nth b 1)) (* (nth a 1) (nth b 0)))])
          vs))

(defn v*s [a & b]
  {:pre  [(vector? a) (every? number? b)]
   :post [(vector? %) (equalSize? (vector %, a))]}
  (let [k (apply * b)]
    (mapv (fn [n] (* n k)) a)))

(defn m*s [a, & b]
  {:pre  [(matrix? a) (every? number? b)]
   :post [(matrix? %) (tensor? (vector %, a))]}
  (let [k (apply * b)]
    (mapv (fn [n] (v*s n k)) a)))

(defn m*v [a b]
  {:pre  [(matrix? a) (vector? b) (equalSize? (vector b, (first a)))]
   :post [(equalSize? (vector a, %)) (vector? %)]}
  (mapv (fn [n] (scalar n b)) a))

(defn transpose [m]
  {:pre  [(matrix? m)]
   :post [(== (count (first %)) (count m)) (matrix? %)]}
  (apply mapv vector m))

(defn m*m [& vs]
  (reduce (fn [a b]
            {:pre  [(matrix? a) (matrix? b) (== (count b) (count (first a)))]
             :post [(matrix? %) (== (count %) (count a)) (== (count (first b)) (count (first %)))]}
            (mapv (fn [n]
                    (mapv (fn [m] (scalar n m)) (transpose b))) a))

          vs))

(defn recOperation [f]
  (fn rec [& vs]
    {:pre  [(tensor? vs)]
     :post [(tensor? (vector % (first vs)))]}
    (if (vector? (first vs))
      (apply mapv rec vs)
      (apply f vs))))

(def t+ (recOperation +))
(def t- (recOperation -))
(def t* (recOperation *))
