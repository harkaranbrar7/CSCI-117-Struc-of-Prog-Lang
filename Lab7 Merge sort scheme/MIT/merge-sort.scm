(define split
  (lambda (l)
    (if (null? l)
        (list '() '())
        (if (null? (cdr l))
            (list l '())
            (let ((rest (split (cdr (cdr l)))))
              (list (cons (car l) (car rest))
                    (cons (car (cdr l)) (car (cdr rest)))))))))

(define merge
  (lambda (l1 l2)
    (if (null? l1)
        l2
        (if (null? l2)
            l1
            (if (< (car l1) (car l2))
                (cons (car l1) (merge (cdr l1) l2))
                (cons (car l2) (merge (cdr l2) l1)))))))

(define merge-sort
  (lambda (l)
    (if (null? l)
        '()
        (if (null? (cdr l))
            l
            (let ((s (split l)))
              (let ((a (car s)) (b (car (cdr s))))
                (merge (merge-sort a) (merge-sort b))))))))