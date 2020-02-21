// (c) 2020 Takamitsu Endo
//
// This file is part of CubicPadSynth.
//
// CubicPadSynth is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CubicPadSynth is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with CubicPadSynth.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <memory>
#include <sstream>
#include <string>

#include "Widget.hpp"

class TextView : public NanoWidget {
public:
  float textSize = 18.0f;

  explicit TextView(NanoWidget *group, std::string content, FontId fontId)
    : NanoWidget(group), fontId(fontId)
  {
    std::stringstream ss(content);
    std::string line;
    while (std::getline(ss, line, '\n')) {
      if (line.size() <= 0)
        str.push_back(" ");
      else
        str.push_back(line);
    }
  }

  void onNanoDisplay() override
  {
    resetTransform();
    translate(getAbsoluteX(), getAbsoluteY());

    // Text.
    fillColor(foregroundColor);
    fontFaceId(fontId);
    textAlign(align);
    fontSize(textSize);
    for (size_t idx = 0; idx < str.size(); ++idx)
      text(0.0f, idx * (textSize + 2), str[idx].c_str(), nullptr);
  }

protected:
  Color backgroundColor{0xff, 0xff, 0xff};
  Color foregroundColor{0, 0, 0};
  Color highlightColor{0x22, 0x99, 0xff};

  std::vector<std::string> str;
  FontId fontId = -1;
  int align = ALIGN_BASELINE | ALIGN_MIDDLE;
};

class TextTableView : public NanoWidget {
public:
  const char rowDelimiter = '\n';
  const char colDelimiter = '|';
  float textSize = 18.0f;

  explicit TextTableView(
    NanoWidget *group, std::string content, float cellWidth, FontId fontId)
    : NanoWidget(group), cellWidth(cellWidth), fontId(fontId)
  {
    std::stringstream ssContent(content);
    std::string line;
    std::string cell;
    while (std::getline(ssContent, line, rowDelimiter)) {
      table.push_back(std::vector<std::string>());
      std::stringstream ssLine(line);
      while (std::getline(ssLine, cell, colDelimiter)) {
        if (cell.size() <= 0)
          table.back().push_back(" ");
        else
          table.back().push_back(cell);
      }
    }
  }

  void onNanoDisplay() override
  {
    resetTransform();
    translate(getAbsoluteX(), getAbsoluteY());

    // Text.
    fillColor(foregroundColor);
    fontFaceId(fontId);
    textAlign(align);
    fontSize(textSize);
    for (size_t row = 0; row < table.size(); ++row)
      for (size_t col = 0; col < table[row].size(); ++col)
        text(col * cellWidth, row * (textSize + 2), table[row][col].c_str(), nullptr);
  }

protected:
  Color backgroundColor{0xff, 0xff, 0xff};
  Color foregroundColor{0, 0, 0};
  Color highlightColor{0x22, 0x99, 0xff};

  std::vector<std::vector<std::string>> table;
  float cellWidth = 100.0f;
  FontId fontId = -1;
  int align = ALIGN_BASELINE | ALIGN_MIDDLE;
};
