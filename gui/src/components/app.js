import React from 'react';
import { connect } from 'react-redux';

import { createBoard } from '../actions';

class App extends React.Component {
  constructor(props) {
    super(props);
    this.state = {

    };
  }

  render() {
    return (
      <div className="app-container">
        <button type="button" onClick={() => this.props.createBoard(3)}>Button</button>
      </div>
    );
  }
}

export default connect(null, { createBoard })(App);
