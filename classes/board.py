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
                piece.setValidMoves(self.board)
    
    # init pieces for a given color
    def initColor(self, color):

        # get the rank based off color
        rank = 7 if color == 'white' else 0

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
        rank = 6 if rank == 7 else 1

        # set the pawns 
        for i in range(0,8): self.board[rank][i] = Pawn(i, rank, color)

    # function to print board
    def printBoard(self):

        # top of board
        print("BOARD:\n_________________________________________________")

        # rows in board
        for row in self.board:
            print("|     |     |     |     |     |     |     |     |")
            print("|", end="")
            for square in row:
                if square:
                    print(f"  {square.getIcon()}  |", end="")
                else: print("     |", end="")
            print("\n|_____|_____|_____|_____|_____|_____|_____|_____|")

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
    
    def possibleMoves(self, pos_x, pos_y):

        color = self.board[pos_y][pos_x].getColor()

        # possible valid squares in row and col
        col = []
        x, y = pos_x, pos_y + 1
        while y < 8:
            if self.board[y][x] and self.board[y][x].getColor() == color: break
            col.append((x, y))
            if self.board[y][x] and self.board[y][x].getColor() != color: break
            y += 1
        
        y = pos_y - 1
        while y >= 0:
            if self.board[y][x] and self.board[y][x].getColor() == color: break
            col.append((x, y))
            if self.board[y][x] and self.board[y][x].getColor() != color: break
            y -= 1
        
        row = []
        x, y = pos_x + 1, pos_y
        while x < 8:
            if self.board[y][x] and self.board[y][x].getColor() == color: break
            row.append((x, y))
            if self.board[y][x] and self.board[y][x].getColor() != color: break
            x += 1
        
        x = pos_x - 1
        while x >= 0:
            if self.board[y][x] and self.board[y][x].getColor() == color: break
            row.append((x, y))
            if self.board[y][x] and self.board[y][x].getColor() != color: break
            x -= 1

        # squares to left and up in the left-to-right diagonal
        ltr_diagonal = []
        x, y = pos_x-1, pos_y-1
        while x >= 0 and y >= 0:
            if self.board[y][x] and self.board[y][x].getColor() == color: break
            ltr_diagonal.append((x, y))
            if self.board[y][x] and self.board[y][x].getColor() != color: break
            x -= 1
            y -= 1

        # squares to right and down in left to right diagonal
        x, y = pos_x+1, pos_y+1
        while x < 8 and y < 8:
            if self.board[y][x] and self.board[y][x].getColor() == color: break
            ltr_diagonal.append((x, y))
            if self.board[y][x] and self.board[y][x].getColor() != color: break
            x += 1
            y += 1
        
        # squares to right and up in right to left diagonal
        rtl_diagonal = []
        x, y = pos_x-1, pos_y+1
        while x >= 0 and y < 8:
            if self.board[y][x] and self.board[y][x].getColor() == color: break
            rtl_diagonal.append((x, y))
            if self.board[y][x] and self.board[y][x].getColor() != color: break
            x -= 1
            y += 1

        # squares to left and down in right to left diagonal
        x, y = pos_x+1, pos_y-1
        while x < 8 and y >= 0:
            if self.board[y][x] and self.board[y][x].getColor() == color: break
            rtl_diagonal.append((x, y))
            if self.board[y][x] and self.board[y][x].getColor() != color: break
            x += 1
            y -= 1
        
        # squares in knight moves
        knight_dirs = [(-1,2),(1,2),(2,1),(2,-1),(-2,1),(-2,-1),(-1,-2),(1,-2)]
        knight_moves = []
        for x, y in knight_dirs:
            x += pos_x
            y += pos_y
            if 0 <= x < 8 and 0 <= y < 8:
                if self.board[y][x] and self.board[y][x].getColor() == color: break
                knight_moves.append((x, y))
        
        # tuple with found moves
        return (col, row, ltr_diagonal, rtl_diagonal, knight_moves)

chess = Board()
chess.printBoard()
for idx_row, row in enumerate(chess.board):
    for idx_col, piece in enumerate(row):
        if piece:
            print(f"POSSIBLE MOVES FOR {piece.getIcon()} AT ({idx_col},{idx_row}): {piece.getValidMoves()}")
