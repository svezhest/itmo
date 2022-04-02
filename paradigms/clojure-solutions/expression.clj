; ---------- HW 10 ----------

(defn fnFactory [f]
      (fn [& args]
          (fn [var]
              (apply f (map #(% var) args)))))

(def constant constantly)
(defn variable [name] #(% name))

(def add (fnFactory +))
(def subtract (fnFactory -))
(def multiply (fnFactory *))
(def fixed-division (fn ([fst] (/ 1. fst))
                        ([fst & rst] (/ (double fst) (apply * rst)))))
(def divide (fnFactory fixed-division))
(def negate subtract)
(def med (fnFactory #(nth (sort %&) (quot (count %&) 2))))
(def avg-function #(/ (apply + %&) (count %&)))
(def avg (fnFactory avg-function))

; ---------- HW 11 ----------

(defn proto-get [obj key]
      (cond
        (contains? obj key) (obj key)
        (contains? obj :prototype) (proto-get (obj :prototype) key)
        :else nil))

(defn proto-call [this key & args]
      (apply (proto-get this key) this args))

(defn field [key]
      (fn [this] (proto-get this key)))

(defn method [key]
      (fn [this & args] (apply proto-call this key args)))

(defn constructor [ctor prototype]
      (fn [& args] (apply ctor {:prototype prototype} args)))

(def evaluate (method :evaluate))
(def toString (method :toString))
(def toStringInfix (method :toStringInfix))
(def diff (method :diff))

(declare ZERO)

(def _ConstantPrototype
  {:evaluate      (fn [this vs] (this :value))
   :diff          (fn [this d] ZERO)
   :toString      (fn [this] (format "%.1f" (double (this :value))))
   :toStringInfix toString
   })
(defn _Constant [this x]
      (assoc this
             :value x))

(def Constant (constructor _Constant _ConstantPrototype))

(def ZERO (Constant 0))
(def ONE (Constant 1))
(def TWO (Constant 2))
(def E (Constant Math/E))

(def _VariablePrototype
  {:evaluate      (fn [this vs] (vs (this :name)))
   :diff          (fn [this d] (if (= d (this :name)) ONE ZERO))
   :toString      (fn [this] (str (this :name)))
   :toStringInfix toString
   })

(defn _Variable [this x]
      (assoc this
             :name x))

(def Variable (constructor _Variable _VariablePrototype))

(def _OperationPrototype (let [_f (field :f)
                               _symbol (field :symbol)
                               _df (field :df)
                               _operands (field :operands)]
  {:evaluate      (fn [this vs] (apply (_f this) (mapv #(evaluate % vs) (_operands this))))
   :diff          (fn [this d] ((_df this) (_operands this) (map #(diff % d) (_operands this))))
   :toString      (fn [this] (str "(" (_symbol this) " " (clojure.string/join " " (map toString (_operands this))) ")"))
   :toStringInfix (fn [this] (if (== (count (_operands this)) 1) (str (_symbol this) "(" (toStringInfix (first (_operands this))) ")")
                                                                 (str "(" (clojure.string/join (str " " (_symbol this) " ") (map toStringInfix (_operands this))) ")")))
   }))

(defn op-factory [f df symbol]
  (constructor
    (fn [this & args] (assoc this :operands args))
    {:prototype _OperationPrototype
     :f f
     :df df
     :symbol symbol}))

(declare Add)
(defn add-diff [args ds] (apply Add ds))
(declare Subtract)
(defn subtract-diff [args ds] (apply Subtract ds))

(def Add (op-factory + add-diff '+))
(def Sum (op-factory + add-diff 'sum))
(def Subtract (op-factory - subtract-diff '-))

(def Negate (op-factory (comp - +) #(Negate (add-diff %1 %2)) 'negate))

; :NOTE: Унарное *
; Унарное умножение работает правильно. (Multiply x)' = 1 * dx + 0 * x

(def Multiply
  (op-factory * (fn [args ds]
                    (second (reduce (fn [[a da] [b db]]
                                        [(Multiply a b) (Add (Multiply a db) (Multiply b da))])
                                    [ONE ZERO]
                                    (map vector args ds)))) '*))
(declare divide-diff)
(def Divide (op-factory fixed-division (fn [args ds] (apply divide-diff (map vector args ds))) '/))

(def divide-diff (fn ([[a da]]
                      (Subtract ZERO (Divide da (Multiply a a))))
                     ([[a da] [b db]]
                      (Divide (Subtract (Multiply da b) (Multiply a db))
                              (Multiply b b)))
                     ([fst snd & rst]
                      (reduce divide-diff (apply vector fst snd rst)))))

(def Avg (op-factory avg-function (fn [args ds] (Divide (apply Add ds) (Constant (count ds)))) 'avg))

; ---------- HW 12 ----------

; copypaste

(defn -return [value tail] {:value value :tail tail})
(def -valid? boolean)
(def -value :value)
(def -tail :tail)
(defn _show [result]
      (if (-valid? result) (str "-> " (pr-str (-value result)) " | " (pr-str (apply str (-tail result))))
                           "!"))
(defn tabulate [parser inputs]
      (run! (fn [input] (printf "    %-10s %s\n" (pr-str input) (_show (parser input)))) inputs))
(defn _empty [value] (partial -return value))
(defn _char [p]
      (fn [[c & cs]]
          (if (and c (p c)) (-return c cs))))
(defn _map [f result]
      (if (-valid? result)
        (-return (f (-value result)) (-tail result))))
(defn _combine [f a b]
      (fn [str]
          (let [ar ((force a) str)]
               (if (-valid? ar)
                 (_map (partial f (-value ar))
                       ((force b) (-tail ar)))))))
(defn _either [a b]
      (fn [str]
          (let [ar ((force a) str)]
               (if (-valid? ar) ar ((force b) str)))))
(defn _parser [p]
      (fn [input]
          (-value ((_combine (fn [v _] v) p (_char #{\u0000})) (str input \u0000)))))
(defn +char [chars] (_char (set chars)))
(defn +char-not [chars] (_char (comp not (set chars))))
(defn +map [f parser] (comp (partial _map f) parser))
(def +parser _parser)
(def +ignore (partial +map (constantly 'ignore)))
(defn iconj [coll value]
      (if (= value 'ignore) coll (conj coll value)))
(defn +seq [& ps]
      (reduce (partial _combine iconj) (_empty []) ps))
(defn +seqf [f & ps] (+map (partial apply f) (apply +seq ps)))
(defn +seqn [n & ps] (apply +seqf (fn [& vs] (nth vs n)) ps))
(defn +or [p & ps]
      (reduce _either p ps))
(defn +opt [p]
      (+or p (_empty nil)))
(defn +star [p]
      (letfn [(rec [] (+or (+seqf cons p (delay (rec))) (_empty ())))] (rec)))
(defn +plus [p] (+seqf cons p (+star p)))
(def *space (+char " \t\n\r"))
(def *ws (+ignore (+star *space)))
(defn +str [p] (+map (partial apply str) p))
(def *digit (+char "0123456789"))
(def *all-chars (mapv char (range 32 128)))
(def *letter (+char (apply str (filter #(Character/isLetter %) *all-chars))))

; my code

(defn bitwise-operation [f]
      (fn [& args]
          (Double/longBitsToDouble (apply f (mapv #(Double/doubleToLongBits %) args)))))
(def And (op-factory (bitwise-operation bit-and) nil "&"))
(def Or (op-factory (bitwise-operation bit-or) nil "|"))
(def Xor (op-factory (bitwise-operation bit-xor) nil "^"))

(defn reduce-left ([f a b] (f a b)) ([f a b & rest] (f a (apply reduce-left f b rest))))

(declare Log)
(declare Pow)

(defn log-diff [[x dx] [y dy]] (Subtract
                                 (Divide
                                   dy
                                   (Multiply y (Log E x)))
                                 (Divide
                                   (Multiply dx (Log x y))
                                   (Multiply x (Log E x)))))

(defn pow-diff [[x dx] [y dy]]
      (Multiply
        (Pow x (Subtract y ONE))
        (Add
          (Multiply y dx)
          (Multiply
            x
            (Multiply (Log E x) dy)))))


(def Log (op-factory (partial reduce-left (fn [x y] (/ (Math/log (Math/abs y))
                                                       (Math/log (Math/abs x)))))
                     (fn [args ds] (second (reduce-left log-diff (map vector args ds)))) "//"))

(def Pow (op-factory (partial reduce-left (fn [x y] (Math/pow x y)))
                     (fn [args ds] (second (reduce-left pow-diff (map vector args ds)))) "**"))

; ---------- parsers and maps ----------

(defn common-parse [dict c v]
      (fn [expr] (letfn [(parse [token]
                                (cond
                                  (number? token) (c token)
                                  (symbol? token) (v (str token))
                                  (list? token) (apply (dict (str (first token))) (map #(parse %) (rest token)))))]
                        (parse (read-string expr)))))

(def functional-operations {"+"      add,
                            "-"      subtract,
                            "*"      multiply,
                            "/"      divide,
                            "negate" negate,
                            "med"    med,
                            "avg"    avg
                            })

(def object-operations {"+"      Add,
                        "-"      Subtract,
                        "*"      Multiply,
                        "/"      Divide,
                        "negate" Negate,
                        "sum"    Sum,
                        "avg"    Avg,
                        "&"      And,
                        "|"      Or,
                        "^"      Xor,
                        "//"     Log,
                        "**"     Pow
                        })

; :NOTE: копипаста
(def parseFunction (common-parse functional-operations constant variable))
(def parseObject (common-parse object-operations Constant Variable))

(defn +op [p] (+map (comp (partial object-operations) str) p))
(defn *str [input] (apply +seqf str (map (comp +char str) input)))
(defn *star-no-ws [p] (+star (+map first (+seq p *ws))))

(def *number (+seqf
               (fn [& data] (read-string (apply str (flatten data))))
               (+opt (+char "+-"))
               (+plus *digit)
               (+opt (+char "."))
               (+star *digit)))

(def *variable (+map Variable (+str (+plus (+char "xyzXYZ")))))
(def *constant (+map Constant *number))
(def *negate (+op (*str "negate")))

(defn +unary-fold [[uns v]]
      (letfn [(rec
                ([] v)
                ([op] (op v))
                ([op & r] (op (apply rec r))))] (apply rec uns)))

(declare *bracket)

(def *operand
  (+map +unary-fold (+seq *ws (*star-no-ws *negate)
                          (+or *constant *variable (delay *bracket)))))
(def *infix-fold-reverse (fn ([a] a)
                             ([a b c] (b a c))
                             ([a b c & vs] (b a (apply *infix-fold-reverse c vs)))))

(def *infix-fold (fn ([a] a)
                     ([a b c & vs] (apply *infix-fold (b a c) vs))))

(defn +fixed-expr [fold-type op-type]
      (fn [val-type]
          (+map (partial apply fold-type) (+map flatten (+seq *ws val-type *ws (+star (+seq op-type *ws val-type *ws)))))))

(defn +left-expr [& ps] (+fixed-expr *infix-fold (apply +or ps)))
(defn +right-expr [& ps] (+fixed-expr *infix-fold-reverse (apply +or ps)))

(def *multiply (+op (+char "*")))
(def *divide (+op (+char "/")))
(def *add (+op (+char "+")))
(def *subtract (+op (+char "-")))
(def *and (+op (+char "&")))
(def *or (+op (+char "|")))
(def *xor (+op (+char "^")))
(def *log (+op (*str "//")))
(def *pow (+op (*str "**")))

(defn *parse-priority [parser & rest]
  (parser
   (if (empty? rest)
     *operand
     (apply *parse-priority rest))))

(def *expression (*parse-priority (+left-expr *xor)
                                  (+left-expr *or)
                                  (+left-expr *and)
                                  (+left-expr *add *subtract)
                                  (+left-expr *multiply *divide)
                                  (+right-expr *pow *log)))

(def *bracket (+seqn 1 (+char "(") *expression (+char ")")))

(def parseObjectInfix (+parser *expression))
