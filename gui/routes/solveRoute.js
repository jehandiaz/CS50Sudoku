import React from "react";
import express from "express";
import { renderToString } from "react-dom/server";
import hbs from "handlebars";

import SolveEnter from "../components/solveEnter.jsx";
import SolvedBoard from "../components/solvedBoard.jsx";

const router = express.Router();

router.get("/", async (req, res) => {
  const theHtml = `
    <html>
      <head><title>Team Rocket's Sudoku</title></head>
      <body>
        <h1>Enter Board</h1>
        <div id="reactele">{{{reactele}}}</div>
        <div>${req.params.board}</div>
        <script src="/solveEnter.js" charset="utf-8"></script>
        <script src="/vendor.js" charset="utf-8"></script>
      </body>
    </html>
  `;

  const hbsTemplate = hbs.compile(theHtml);
  const solveComp = renderToString(<SolveEnter />);
  const htmlToSend = hbsTemplate({ reactele: solveComp });
  res.send(htmlToSend);
});

router.get("/:board", async (req, res) => {
  const theHtml = `
    <html>
      <head><title>Team Rocket's Sudoku</title></head>
      <body>
        <h1>Solved Board</h1>
        <div id="reactele">{{{reactele}}}</div>
        <div>${req.params.board}</div>
        <script src="/solvedBoard.js" charset="utf-8"></script>
        <script src="/vendor.js" charset="utf-8"></script>
      </body>
    </html>
  `;

  const hbsTemplate = hbs.compile(theHtml);
  const solveComp = renderToString(<SolvedBoard />);
  const htmlToSend = hbsTemplate({ reactele: solveComp });
  res.send(htmlToSend);
});

export default router;