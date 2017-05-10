(defvar a)
(defvar b)
(defvar c)
(defvar d)

(write-line "Enter two numners with prefix #b :")
(terpri)

(setf a(read))
(setf b(read))


(sb-thread:make-thread(lambda()
	(setf c(+ a b))
	(print "Addition in Binary")
	(format t "~b" c)
	(print "Addition in Decimal")
	(format t "~d" c)
	(print "Addition in Octal")
	(format t "~o" c)
	(print "Addition in Hex")
	(format t "~x" c)
	(terpri)

))

(sb-thread:make-thread(lambda()
	(setf c(- a b))
	(print "Subtraction in Binary")
	(format t "~b" c)
	(terpri)

))

(sb-thread:make-thread(lambda()
	(setf c(* a b))
	(print "Multiplication in Binary")
	(format t "~b" c)
	(terpri)

))

(sb-thread:make-thread(lambda()
	(setf c(* a a))
	(print "Square of First number in binary")
	(format t "~b" c)
	(terpri)

))

(sb-thread:make-thread(lambda()
	(setf c(* b b b))
	(print "Cube of Second number in binary")
	(format t "~b" c)
	(terpri)

))

(sb-thread:make-thread(lambda()
	(setf c(sin a))
	(print "Sin of first number in binary")
	(print c)
	(terpri)

))

(sb-thread:make-thread(lambda()
	(setf c(cos a))
	(print "Cos of first number in binary")
	(print c)
	(terpri)

))

(sb-thread:make-thread(lambda()
	
	(setf c(tan a))
	(print "tan of first number in binary")
	(print c)
	(terpri)

))

(sb-thread:make-thread(lambda()
	(setf c(min a b))
	(print "minimum number in Decimal")
	(format t "~d" c)
	(terpri)

))

(sb-thread:make-thread(lambda()
	(setf c(max a b))
	(print "maximum number in Decimal")
	(format t "~d" c)
	(terpri)

))


pccoe@DMSA-19:~/Desktop/@@@$ sbcl
This is SBCL 1.1.14.debian, an implementation of ANSI Common Lisp.
More information about SBCL is available at <http://www.sbcl.org/>.

SBCL is free software, provided as is, with absolutely no warranty. It is mostly in the public domain; some portions are provided under BSD-style licenses.  See the CREDITS and COPYING files in the distribution for more information.
* (load "Mytest.lisp")
 Enter two numbers in binary format with prefix #b : 
 #b 11
 #b 10

" Addition in Binary     	: " 	101
" Addition in Decimal  	: "  	5
" Addition in Octal  		: "  	5
" Addition in Hex  		: "  	5

" Subtraction in Binary  	: "  	1

" Multipliaction in Binary	: "  	110

" Square of First number in binary : " 1001

" Cube of Second number in binary  : " 1000

" Sin of first number in binary    : " 0.14112

" Cos of first number in binary	   : " -0.9899925

" tan of first number in binary    : " -0.14254655

"minimum number in Decimal		: "  	2
"maximum number in Decimal		: "  	3
T  *


