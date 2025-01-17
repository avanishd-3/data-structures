use std::fmt;
use std::ops::Index;


struct DiagonalMatrix<T> {
    matrix: Vec<Vec<T>>,
    num_rows: usize,
    num_cols: usize,
}

impl<T: std::fmt::Debug + Default + Copy> DiagonalMatrix<T> {

    fn new(col_size: usize) -> Self {
        return DiagonalMatrix { matrix: Vec::new(), num_rows: 0, num_cols: col_size };
    }

    fn add_row(&mut self, val: T) {
        let mut row: Vec<T> = Vec::new();
        
        for i in 0..(self.num_cols) {
            if i == self.num_rows {
                row.push(val);
            } else {
                row.push(T::default());
            }
        }
        self.matrix.push(row);
        self.num_rows += 1;
    }
}

// Allow matrix to be printed

impl<T: std::fmt::Debug> fmt::Debug for DiagonalMatrix<T> {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        for i in 0..self.num_rows {
            for j in 0..self.num_cols {
                write!(f, "{:?} ", self.matrix[i][j])?;
            }
            writeln!(f)?;
        }
        Ok(())
    }
}

// Like [] operator in C++

impl<T> Index<usize> for DiagonalMatrix<T> {
    type Output = Vec<T>;

    fn index(&self, index: usize) -> &Self::Output {
        return &self.matrix[index]
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn new_matrix_has_zero_rows() {
        let matrix: DiagonalMatrix<isize> = DiagonalMatrix::new(2);
        assert_eq!(matrix.num_rows, 0);
    }

    #[test]
    fn matrix_has_one_row_after_insertion() {
        let mut matrix: DiagonalMatrix<isize> = DiagonalMatrix::new(2);
        matrix.add_row(1);
        assert_eq!(matrix.num_rows, 1);
    }

    #[test]
    fn matrix_indexing_works_if_there_is_one_row() {
        let mut matrix: DiagonalMatrix<isize> = DiagonalMatrix::new(5);
        matrix.add_row(1);
        let top_row = matrix[0].clone();
        assert_eq!(top_row, vec![1, 0, 0, 0, 0]);
    }

    #[test]
    fn matrix_indexing_works_if_there_is_multiple_rows() {
        let mut matrix: DiagonalMatrix<isize> = DiagonalMatrix::new(5);
        matrix.add_row(1);
        matrix.add_row(2);

        let first_row = matrix[0].clone();
        let second_row = matrix[1].clone();

        assert_eq!(first_row, vec![1, 0, 0, 0, 0]);
        assert_eq!(second_row, vec![0, 2, 0, 0, 0]);
    }

    #[test]
    fn matrix_prints_correctly() {
        let mut matrix: DiagonalMatrix<isize> = DiagonalMatrix::new(5);
        matrix.add_row(1);
        matrix.add_row(2);

        let expected_output = "1 0 0 0 0 \n0 2 0 0 0 \n";
        assert_eq!(format!("{:?}", matrix), expected_output);

    }
}