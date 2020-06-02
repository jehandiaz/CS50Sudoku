/* eslint-disable react/no-array-index-key */
import React from 'react';
import { connect } from 'react-redux';

import { createBoard, solveBoard } from '../actions/boardActions';
import { createErrorSelector } from '../actions/errorActions';
import { createLoadingSelector } from '../actions/loadingActions';

import './app.scss';

class App extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      posRow: -1,
      posCol: -1,

      difficulty: 3,
    };
  }

  isHighlighted(ri, ci) {
    if (ri === this.state.posRow && ci === this.state.posCol) return false; // Don't highlight selected square
    if (this.state.posRow === ri || this.state.posCol === ci) return true; // In same row or column
    return false;
  }

  renderBoard() {
    return (
      <div className="app-board-container">
        {/* {JSON.stringify(this.props.board)} */}
        {this.props.board.map((r, ri) => {
          return (
            <div key={ri} className="app-board-row-container">
              {r.map((c, ci) => {
                return (
                  <div
                    key={`${ri} ${ci}`}
                    className={`app-board-cell-container${this.isHighlighted(ri, ci) ? ' highlighted' : ''}`}
                    onMouseEnter={() => this.setState({ posRow: ri, posCol: ci })}
                  >
                    <p>{c}</p>
                  </div>
                );
              })}
            </div>
          );
        })}
      </div>
    );
  }

  render() {
    return (
      <div className="app-container">
        <h1>Team Rocket Sudoku Solver</h1>

        <button type="button" onClick={() => this.props.createBoard(this.state.difficulty)}>Create Board</button>
        <button type="button" onClick={() => this.props.solveBoard(this.props.board, this.props.dimension)}>Solve Board</button>

        {this.props.board && this.props.dimension
          ? this.renderBoard()
          : null}

        <input
          type="number"
          min={1}
          max={5}
          value={this.state.difficulty}
          onChange={e => this.setState({ difficulty: e.target.value })}
        />

      </div>
    );
  }
}

// Import loading state and error messages of specified actions from redux state
const loadActions = ['FETCH_BOARD'];
const loadingSelector = createLoadingSelector(loadActions);
const errorSelector = createErrorSelector(loadActions);

const mapStateToProps = state => ({
  board: state.board.board,
  dimension: state.board.dimension,
  difficulty: state.board.difficulty,

  isLoading: loadingSelector(state),
  errorMessage: errorSelector(state),
});

export default connect(mapStateToProps, { createBoard, solveBoard })(App);
