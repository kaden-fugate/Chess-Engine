from square import Square
from pieces import King, Queen, Rook, Bishop, Knight, Pawn

class Board:

    # board initialization
    def __init__(self):
        self.board = [[Square(i, j, None) for i in range(0,8)] for j in range(0,8)]
        self.initColor('white')
        self.initColor('black')
    
    # init pieces for a given color
    def initColor(self, color):

        # get the rank based off color
        rank = 7 if color == 'white' else 0

        # set the pieces on the back rank
        self.board[rank][0].setPiece( Rook(color) )
        self.board[rank][1].setPiece( Knight(color) )
        self.board[rank][2].setPiece( Bishop(color) )
        self.board[rank][3].setPiece( Queen(color) )
        self.board[rank][4].setPiece( King(color) )
        self.board[rank][5].setPiece( Bishop(color) )
        self.board[rank][6].setPiece( Knight(color) )
        self.board[rank][7].setPiece( Rook(color) )

        # get pawns rank
        rank = 6 if rank == 7 else 1

        # set the pawns 
        for i in range(0,8): self.board[rank][i].setPiece(Pawn(color))

    # function to print board
    def printBoard(self):

        # top of board
        print("BOARD:\n_________________________________________________")

        # rows in board
        for row in self.board:
            print("|     |     |     |     |     |     |     |     |")
            print("|", end=" ")
            for square in row:
                square.printPiece()
            print("\n|_____|_____|_____|_____|_____|_____|_____|_____|")

board = Board()
board.printBoard()