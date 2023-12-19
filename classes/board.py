from pieces import King, Queen, Rook, Bishop, Knight, Pawn

class Board:

    # board initialization
    def __init__(self):

        # init mem for board, init white and black pieces
        self.board = [[None for i in range(0,8)] for j in range(0,8)]
        self.initColor('white')
        self.initColor('black')

        # set all valid moves for each piece on the board
        for rank in (self.board[0], self.board[1], self.board[6], self.board[7]):
            for piece in rank:
                if piece:
                    piece.setValidMoves(self.board)
        
        # get set all of all valid moves for each color
        self.black_moves, self.white_moves = self.getAllValidMoves()
        self.black_checked, self.white_checked = False, False

    # init pieces for a given color
    def initColor(self, color):

        # get the rank based off color
        rank = 0 if color == 'white' else 7

        # set the pieces on the back rank
        self.board[rank][0] = Rook(0, rank, color)
        self.board[rank][1] = Knight(1, rank, color)
        self.board[rank][2] = Bishop(2, rank, color)
        self.board[rank][3] = Queen(3, rank, color)
        if color == 'white': self.board[rank][4] = Queen(4, rank, color)
        else: self.board[rank][4] = King(4, rank, color)
        self.board[rank][5] = Bishop(5, rank, color)
        self.board[rank][6] = Knight(6, rank, color)
        self.board[rank][7] = Rook(7, rank, color)

        # get pawns rank
        rank = 1 if rank == 0 else 6

        # set the pawns 
        for i in range(0,8): self.board[rank][i] = Pawn(i, rank, color)

    # function to print board
    def printBoard(self):

        # top of board
        print("BOARD:\n_________________________________________________")

        # rows in board
        for idx, row in enumerate(reversed(self.board)):
            print(f"|{8 - idx}    |     |     |     |     |     |     |     |")
            print("|", end="")
            for square in row:
                if square:
                    print(f"  {square.getIcon()}  |", end="")
                else: print("     |", end="")
            if idx == 7:
                print("\n|____A|____B|____C|____D|____E|____F|____G|____H|")
            else:
                print("\n|_____|_____|_____|_____|_____|_____|_____|_____|")

    def getAllValidMoves(self):

        black_valid_moves = set()
        white_valid_moves = set()

        # cycle through all squares on board
        for row in self.board:
            for piece in row:

                # if the current square on the board has a piece, add its valid moves to the list
                # of valid moves for the respective team
                if piece:

                    # iterate through each move to add it to the correct colors set of valid moves
                    for move in piece.getValidMoves():
                        
                        if piece.getColor() == 'black': black_valid_moves.add(move)
                        else: white_valid_moves.add(move)
    
        return (black_valid_moves, white_valid_moves)

    # given a board and a color to check for, return whether or not that color is in check.
    def isCheck(self, board, color):

        king_x, king_y = -1, -1
        opposite_color_moves = set()

        for idx_y, row in enumerate(board):
            for idx_x, piece in enumerate(row):

                # if piece is in square
                if piece:
                    
                    # if piece is colors king, mark the coordinates
                    if piece.getColor() == color and (piece.getIcon() == '♔' or piece.getIcon() == '♚'):
                        king_x, king_y = idx_x, idx_y

                    # if piece is of opposite color, add all of its moves to the set of all moves
                    # for the opposite team.
                    elif piece.getColor() != color:
                        for move in piece.getValidMoves():
                            opposite_color_moves.add(move)
                if (king_x, king_y) in opposite_color_moves: return True

        return False

    def notationToPos(self, notation):

        pos_x, pos_y = -1, -1

        # convert rank to y pos
        if notation[0] == 'A': pos_y = 0
        elif notation[0] == 'B': pos_y = 1
        elif notation[0] == 'C': pos_y = 2
        elif notation[0] == 'D': pos_y = 3
        elif notation[0] == 'E': pos_y = 4
        elif notation[0] == 'F': pos_y = 5
        elif notation[0] == 'G': pos_y = 6
        elif notation[0] == 'H': pos_y = 7

        # convert file to x pos
        if notation[1] == '1': pos_x = 0
        elif notation[1] == '2': pos_x = 1
        elif notation[1] == '3': pos_x = 2
        elif notation[1] == '4': pos_x = 3
        elif notation[1] == '5': pos_x = 4
        elif notation[1] == '6': pos_x = 5
        elif notation[1] == '7': pos_x = 6
        elif notation[1] == '8': pos_x = 7

        return (pos_x, pos_y)

chess = Board()
chess.printBoard()
for idx_row, row in enumerate(chess.board):
    for idx_col, piece in enumerate(row):
        pass
        # if piece:
            # print(f"- POSSIBLE MOVES FOR {piece.getIcon()} AT ({idx_col},{idx_row}): {piece.getValidMoves()}")

# black_moves, white_moves = chess.getAllValidMoves()
#print(f"- BLACK VALID MOVES: {black_moves}\n- WHITE VALID MOVES: {white_moves}")
print(f"- BLACK IS IN CHECK: {chess.isCheck(chess.board, 'black')}")