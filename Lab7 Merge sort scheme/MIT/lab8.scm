
;Complete the following functions for Split, Merge and Mergesort functions.
;or, you can use your own ways.


    (define (split x)
       (cond ((null? x) (cons '() '()))
             ((null? (cdr x)) (cons x '()))
             (else ( cons ( cons (car x) (car (split (cddr x))))
              (cons (cadr x) (cdr ( split (cddr x))))
                   )
             )
        )
     )


    (define (merge x y)
       (cond ((null? x) y)
             ((null? y) x)
             (( <= (car x) (car y) ) (cons(car x) (merge (cdr x) y )))
             (else (cons (car y) (merge x (cdr y))))

              )

     )


    (define (mergesort x)
       (cond ((null? x) x)
             ((null? (cdr x)) x)
             (else (let ((split_x (split x)))
                   (merge (mergesort (car split_x))
                          (mergesort (cdr split_x)))
        )
     )
     )

     )
