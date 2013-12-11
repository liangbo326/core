﻿using System;
using System.Collections.Generic;
using System.Text;

namespace ASCOfficeEWSEditor.Editor.Calculation.Formulas.Ptgs.Functions
{
    internal class PtgFuncCos : PtgFuncMathOneArg
    {
        public override DataObjects.IDataObject DoMath(double num_value)
        {
            return new DataObjects.ObjectNumber(Math.Cos(num_value));
        }

        public override string ToString() { return "COS"; }
    }
}
