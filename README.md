# Bike Anti-Theft Device

A portable, concealed device to prevent bike theft and facilitate tracking, centered around the STM32WLCC integrated microcontroller and SubGHz transceiver. This project was created for [ECE445 Spring 2022 at the University of Illinois at Urbana-Champaign](https://courses.physics.illinois.edu/ece445/projects.asp). 


# Development Folder Structure

- *Documentation*: Proposal, design document, final paper, and presentation for ECE 445. 
- *References*: Selected datasheets and reference manuals. 
- *Notebooks*: Lab notebooks during the development process. 
- *Hardware*: KiCAD schematic and layout files for each board used in the project. 
- *Firmware*: Microcontroller code for the STM32WLCC used in our project. Note that the final demo code is in SingleCore_UART -- the other folders contain various debugging firmware projects since it is easier to keep track of things during the development process by re-initializing a project in CubeMX for different tests rather than continuously using the same project. 


# Lab Notebook Structure

- Each group member will write entries in their markdown notebook to describe the development and debugging process. 
- Daily notebook entries must have a descriptive title, date, and the user's name. 
- Notebook entries referring to specific features, etc should identify the feature by its commit hash. For readability it may be better to embed images (of schematics, test setups, hand sketches etc) in the markdown notebook itself depending on the context.
- Lab notebook entries will not be removed or modified once written down. 
- Lab data, code to generate plots, etc is in a different folder since it is shared. Always save the original data for all trials, even if you only end up using some of the data for the analysis. 


# Workflow notes 
- VScode is convenient to write and render markdown. 
- TEXstudio is convenient to write and render LaTEX documents for reports, etc. Always save the .tex source to git, not the generated PDF. 
- Always commit the ENTIRE kicad project directory for PCBs. This prevents issues with footprint and symbol libraries 
since the entire project directory includes the backup and symbol rescue files.

















