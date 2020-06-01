import React from "react";
import { hydrate } from "react-dom";
import SolvedBoard from "./solvedBoard";

hydrate(<SolvedBoard />, document.getElementById("reactele"));