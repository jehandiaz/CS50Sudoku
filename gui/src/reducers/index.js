import { combineReducers } from 'redux';

import boardReducer from './boardReducer';
import errorReducer from './errorReducer';
import loadingReducer from './loadingReducer';

const rootReducer = combineReducers({
  board: boardReducer,
  error: errorReducer,
  loading: loadingReducer,
});

export default rootReducer;
