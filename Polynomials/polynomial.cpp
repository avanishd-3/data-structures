#include <iostream>
#include <cmath>

class Polynomial{
    private:
        struct Term {
            int coefficient;
            int exponent;
            char var;
        };

        int n;
        Term *terms;

    public: 
        Polynomial(int i)
            : n{i}
            , terms(new Term[n])
        {
        }

        ~Polynomial() {
            delete[] terms;
        }

        double evaluate(double v) {
            double sum = 0;
            for (int i = 0; i < n; ++i) {
                sum += terms[i].coefficient * std::pow(v, terms[i].exponent);
            }
            return sum;
        }

        friend std::ostream& operator<<(std::ostream &out, const Polynomial &p) {
            for (int i = 0; i < p.n; ++i) {
                out << p.terms[i].coefficient << p.terms[i].var << "^" << p.terms[i].exponent << " + ";
            }
            out << std::endl;
            return out;
        }

        Polynomial* operator+(Polynomial &p) {
            Polynomial *result = new Polynomial(n + p.n);

            int i,j,k;
            i = j = k = 0;

            while (i < n && j < p.n) {
                if (terms[i].var != p.terms[j].var) { 
                    result->terms[k++] = terms[i++];
                    result->terms[k++] = p.terms[j++];
                }

                else {
                    if (terms[i].exponent != p.terms[j].exponent) { 
                    result->terms[k++] = terms[i++];
                    result->terms[k++] = p.terms[j++];
                    }

                    else {
                        result->terms[k++] = Term{terms[i].coefficient + p.terms[i].coefficient, terms[i].exponent, terms[i].var};
                    }
                }
            }
            // Copy the remaining elements from either the first or second polynomial
            for (;i<n; ++i) { // Copy remaining elements from first polynomial if any
                result->terms[k++] = terms[i];
            }

            for (;j<p.n; ++j) { // Copy remaining elements from second polynomial if any
                result->terms[k++] = p.terms[i];
            }

            // Put actual number of elements
            result->n = k;
            return result;
        }
};