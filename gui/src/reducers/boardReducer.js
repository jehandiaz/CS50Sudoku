import ActionTypes from '../actions';

const initialState = {
  board: [],
  dimension: 0,
  difficulty: 0,
};

const reducer = (state = initialState, action) => {
  switch (action.type) {
    case ActionTypes.FETCH_BOARD_SUCCESS:
      return Object.assign({}, state, { difficulty: action.payload.difficulty, board: action.payload.board.board, dimension: action.payload.board.dimension });
    default:
      return state;
  }
};

export default reducer;
