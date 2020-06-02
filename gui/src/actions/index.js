import axios from 'axios';
import * as constants from '../constants';

const ActionTypes = {
  FETCH_BOARD_REQUEST: 'FETCH_BOARD_REQUEST',
  FETCH_BOARD_SUCCESS: 'FETCH_BOARD_SUCCESS',
  FETCH_BOARD_FAILURE: 'FETCH_BOARD_FAILURE',
};

/**
 * Creates a board with the given difficulty
 * @param {*} difficulty
 */
export function createBoard(difficulty) {
  return dispatch => new Promise((resolve, reject) => {
    dispatch({ type: ActionTypes.FETCH_BOARD_REQUEST });

    axios.post(`${constants.SERVER_URL}/board/create`, { difficulty }).then((response) => {
      console.log(response);
      dispatch({ type: ActionTypes.FETCH_BOARD_SUCCESS, payload: response.data });
      resolve();
    }).catch((error) => {
      console.log(error);
      dispatch({ type: ActionTypes.FETCH_BOARD_FAILURE, payload: error.response.data });
      reject();
    });
  });
}

export function solveBoard(board) {

}

export default ActionTypes;
