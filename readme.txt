A simple project to demonstrate some malware-ish concepts
	- droppers
	- dll injection

Houses 
	- a project that creates a dll that will spawn a simple message box
	- another project that is a dropper that will drop the aforementioned dll at C:\windows\temp and then iterate through the process list looking for calc.exe and inject the dll into calc.exe