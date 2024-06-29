/*
 * Recursively solve a connect 4 position using negamax variant of min-max algorithm.
 * @return the score of a position:
 *  - 0 for a draw game
 *  - positive score if you can win whatever your opponent is playing. Your score is
 *    the number of moves before the end you can win (the faster you win, the higher your score)
 *  - negative score if your opponent can force you to lose. Your score is the oposite of
 *    the number of moves before the end you will lose (the faster you lose, the lower your score).
 */
// int negamax(const Position &P) {
//   if(P.nbMoves() == Position::WIDTH*Position::HEIGHT) // check for draw game
//     return 0;

//   for(int x = 0; x < Position::WIDTH; x++) // check if current player can win next move
//     if(P.canPlay(x) && P.isWinningMove(x))
//       return (Position::WIDTH*Position::HEIGHT+1 - P.nbMoves())/2;

//   int bestScore = -Position::WIDTH*Position::HEIGHT; // init the best possible score with a lower bound of score.

//   for(int x = 0; x < Position::WIDTH; x++) // compute the score of all possible next move and keep the best one
//     if(P.canPlay(x)) {
//       Position P2(P);
//       P2.play(x);               // It's opponent turn in P2 position after current player plays x column.
//       int score = -negamax(P2); // If current player plays col x, his score will be the opposite of opponent's score after playing col x
//       if(score > bestScore) bestScore = score; // keep track of best possible score so far.
//     }

//   return bestScore;
// }

// /**
//  * A class storing a Connect 4 position.
//  * Function are relative to the current player to play.
//  * Position containing aligment are not supported by this class.
//  */
// class Position {
//   public:
//     static const int WIDTH = 7;  // Width of the board
//     static const int HEIGHT = 6; // Height of the board

//     /**
//      * Indicates whether a column is playable.
//      * @param col: 0-based index of column to play
//      * @return true if the column is playable, false if the column is already full.
//      */
//     bool canPlay(int col) const;

//     /**
//      * Plays a playable column.
//      * This function should not be called on a non-playable column or a column making an alignment.
//      *
//      * @param col: 0-based index of a playable column.
//      */
//     void play(int col);

//     /**
//      * Indicates whether the current player wins by playing a given column.
//      * This function should never be called on a non-playable column.
//      * @param col: 0-based index of a playable column.
//      * @return true if current player makes an alignment by playing the corresponding column col.
//      */
//     bool isWinningMove(int col) const;
// };
