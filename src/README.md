# Internal source modules

- executor: Executor implementation and command execution entry point.
- command: Command factory, command composition and atomic action execution.
- pose: Vehicle state, coordinates and direction rules.
- common: Reusable utilities such as the Singleton template.

The public Executor interface stays in ../include. Tests stay in ../tests.
Headers in the same module use local includes. Cross-module includes start
from the src root, for example command/CmderFactory.hpp.

CMake collects .cpp files recursively. Run script/build_and_run.bat from the
project root to configure again after adding or moving source files.
