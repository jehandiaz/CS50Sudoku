import axios from 'axios';

import * as constants from '../constants';
import ActionTypes from '.';

/**
 * Creates a board with the given difficulty
 * @param {*} difficulty
 */
export function createBoard(difficulty) {
  return dispatch => new Promise((resolve, reject) => {
    dispatch({ type: ActionTypes.FETCH_BOARD_REQUEST });

    axios.post(`${constants.SERVER_URL}/board/create`, { difficulty }).then((response) => {
      dispatch({ type: ActionTypes.FETCH_BOARD_SUCCESS, payload: response.data });
      resolve();
    }).catch((error) => {
      console.log(error);
      dispatch({ type: ActionTypes.FETCH_BOARD_FAILURE, payload: error.response.data });
      reject();
    });
  });
}

export function solveBoard(board, dimension) {
  return dispatch => new Promise((resolve, reject) => {
    dispatch({ type: ActionTypes.FETCH_BOARD_REQUEST });

    axios.post(`${constants.SERVER_URL}/board/solve`, { board: { board, dimension } }).then((response) => {
      dispatch({ type: ActionTypes.FETCH_BOARD_SUCCESS, payload: response.data });
      resolve();
    }).catch((error) => {
      console.log(error);
      dispatch({ type: ActionTypes.FETCH_BOARD_FAILURE, payload: error.response.data });
      reject();
    });
  });
}
