import React from 'react';

class SolvedBoard extends React.Component {
  constructor(props) {
    super(props);
    this.state = {

    };
  }

  render() {
    console.log("pathname", window.location.pathname);
    return (
      <div>Solved Board</div>
    );
  }
}

export default SolvedBoard;