/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "../gcode.h"
#include "../../module/tool_change.h"

#if ENABLED(DEBUG_LEVELING_FEATURE) || EXTRUDERS > 1
  #include "../../module/motion.h"
#endif

/**
 * T0-T3: Switch tool, usually switching extruders
 *
 *   F[units/min] Set the movement feedrate
 *   S1           Don't move the tool in XY after change
 */
void GcodeSuite::T(const uint8_t tool_index) {

  #if ENABLED(DEBUG_LEVELING_FEATURE)
    if (DEBUGGING(LEVELING)) {
      SERIAL_ECHOPAIR(">>> T(", tool_index);
      SERIAL_CHAR(')');
      SERIAL_EOL();
      DEBUG_POS("BEFORE", current_position);
    }
  #endif

  #if EXTRUDERS < 2

    tool_change(tool_index);

  #else

    tool_change(
      tool_index,
      MMM_TO_MMS(parser.linearval('F')),
      (tool_index == active_extruder) || parser.boolval('S')
    );

  #endif

  #if ENABLED(DEBUG_LEVELING_FEATURE)
    if (DEBUGGING(LEVELING)) {
      DEBUG_POS("AFTER", current_position);
      SERIAL_ECHOLNPGM("<<< T()");
    }
  #endif
}
