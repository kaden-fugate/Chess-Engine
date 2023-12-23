from pieces import King, Queen, Rook, Bishop, Knight, Pawn
from errors import invalidMoveError

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
        self.current_turn = 'white'

    # init pieces for a given color
    def initColor(self, color):

        # get the rank based off color
        rank = 0 if color == 'white' else 7

        # set the pieces on the back rank
        self.board[rank][0] = Rook(0, rank, color)
        self.board[rank][1] = Knight(1, rank, color)
        self.board[rank][2] = Bishop(2, rank, color)
        self.board[rank][3] = Queen(3, rank, color)
        self.board[rank][4] = King(4, rank, color)
        self.board[rank][5] = Bishop(5, rank, color)
        self.board[rank][6] = Knight(6, rank, color)
        self.board[rank][7] = Rook(7, rank, color)

        # get pawns rank
        rank = 1 if rank == 0 else 6

        # set the pawns 
        for i in range(0,8): self.board[rank][i] = Pawn(i, rank, color)

    def updatePieces(self):

        for row in self.board:
            for piece in row:

                if piece:
                    piece.setValidMoves(self.board)

    # function to print board
    def printBoard(self):

        # top of board
        print("_________________________________________________")

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

                if (king_x, king_y) in opposite_color_moves:
                    return True

        return False

    def takeTurn(self):

        turn = 'White' if self.current_turn == 'white' else 'Black'
        print(f"\n{turn}'s Turn:")
        self.printBoard()

        while True:
            try:
                move = input("Please Input Your Move: ")

                start = self.notationToPos(move[0] + move[1])
                end = self.notationToPos(move[2] + move[3])

                self.movePiece(start, end)
                break
            
            except invalidMoveError as err:
                print(err)

        self.current_turn = 'white' if self.current_turn == 'black' else 'black'

    def movePiece(self, start_pos, end_pos):

        # get x and y coords for start and end positions
        start_x, start_y = start_pos
        end_x, end_y = end_pos

        # get positions on board
        start = self.board[start_y][start_x]

        # if start position on board doesnt have piece, no piece to move therefore we should raise
        # an invalid move error.
        if not start: 
            raise invalidMoveError(f"Invalid Move Error: No Piece at Position {start_pos}")

        # if piece at start position is not the color is not that of the current turns color, 
        # current move is invalid.
        elif start.getColor() != self.current_turn: 
            raise invalidMoveError(f"Invalid Move Error: Piece at Position {start_pos} is not {self.current_turn}")

        # if end position for piece is not 
        elif end_pos not in start.getValidMoves(): 
            raise invalidMoveError(f"Invalid Move Error: Piece at {start_pos} can't Move to {end_pos}")
        
        if self.isAttemptingToCastle(start_pos, end_pos):

            self.board[start_y][start_x].canCastle(self.board, self.current_turn)

            # short castle 
            if end_x - start_x > 0:

                # if the king can castle short
                if self.board[start_y][start_x].getCastleShort():
                    self.castle(True)
                
                # raise error if the king couldnt castle
                else: raise invalidMoveError(f"Invalid Move Error: King at {start_pos} can't Castle Short")

            # long castle
            else:

                if self.board[start_y][start_x].getCastleLong(): self.castle(False)

                # raise error if the king couldnt castle
                else: raise invalidMoveError(f"Invalid Move Error: King at {start_pos} can't Castle Long")

        # move the piece
        self.board[end_y][end_x] = start
        self.board[start_y][start_x] = None
        self.updatePieces()

        # if this move will put our king in check, the move is invalid. reverse the move and
        # raise invalid move error
        if self.isCheck(self.board, self.current_turn):
            self.board[start_y][start_x] = start
            self.board[end_y][end_x] = None
            self.updatePieces()
            raise invalidMoveError(f"Invalid Move Error: Moving Piece from {start_pos} to {end_pos} will Kill the King")

        # update the pieces coordinates and set its "hasMoved" data member
        self.board[end_y][end_x].setCoords((end_x, end_y))
        self.board[end_y][end_x].setHasMoved()

    def castle(self, is_short):

        # get rank and file for easy indexing
        rank = 0 if self.current_turn == 'white' else 7
        rook_file = 5 if is_short else 3

        # all of our pieces we might need
        short_rook = self.board[rank][7]
        long_rook = self.board[rank][0]

        # if we're dealing with a short castle, we can set the new coords, update has moved, move
        # the piece to its new place and delete it from the old position
        if is_short:

            short_rook.setCoords((rook_file,rank))
            short_rook.setHasMoved()
            self.board[rank][rook_file] = short_rook
            self.board[rank][7] = None

        # same rules with long castle as we have for short but we'll be dealing with the 
        # 'long_rook' variable now instead of the 'short_rook' one
        else:

            long_rook.setCoords((rook_file,rank))
            long_rook.setHasMoved()
            self.board[rank][rook_file] = long_rook
            self.board[rank][0] = None

    def isAttemptingToCastle(self, start_pos, end_pos):
        
        long_rook = (7,0) if self.current_turn == 'white' else (0,7)
        short_rook = (0,0) if self.current_turn == 'white' else (7,7)

        start_x, start_y = start_pos
        end_x, end_y = end_pos

        # if current piece is king
        if self.board[start_y][start_x].getIcon() == '♔' or self.board[start_y][start_x].getIcon() == '♚':

            # and end pos is two from start pos (x axis), then king is attempting to castle
            if abs(start_x - end_x) == 2: return True
        
        # else, king not attempting case
        return False

    def notationToPos(self, notation):

        pos_x, pos_y = -1, -1

        if notation == 'OO':
            return (6,0) if self.current_turn == 'white' else (6,7)
        elif notation == 'OOO':
            return (2,0) if self.current_turn == 'white' else (2,7)

        # convert rank to y pos
        if notation[0] == 'A' or notation[0] == 'a': pos_x = 0
        elif notation[0] == 'B' or notation[0] == 'b': pos_x = 1
        elif notation[0] == 'C' or notation[0] == 'c': pos_x = 2
        elif notation[0] == 'D' or notation[0] == 'd': pos_x = 3
        elif notation[0] == 'E' or notation[0] == 'e': pos_x = 4
        elif notation[0] == 'F' or notation[0] == 'f': pos_x = 5
        elif notation[0] == 'G' or notation[0] == 'g': pos_x = 6
        elif notation[0] == 'H' or notation[0] == 'h': pos_x = 7

        # convert file to x pos
        if notation[1] == '1': pos_y = 0
        elif notation[1] == '2': pos_y = 1
        elif notation[1] == '3': pos_y = 2
        elif notation[1] == '4': pos_y = 3
        elif notation[1] == '5': pos_y = 4
        elif notation[1] == '6': pos_y = 5
        elif notation[1] == '7': pos_y = 6
        elif notation[1] == '8': pos_y = 7

        return (pos_x, pos_y)

chess = Board()
for _ in range(0, 20):
    chess.takeTurn()