# Sales-History
An app to output data of a transaction log via various methods.

Summarize the project and what problem it was solving.
This project addresses the issue of displaying and organizing data from a Point of Sale system (or manual ledger) in order for the end-user to make decisions based on acquired information.

What did you do particularly well?
Breaking up the methods by functionality and accessing them from the C++ UI was clean and effective.
Additionally, I believe the additional methods (To display the histogram in ascending and descending order) I've added outside of the prompt for this project are helpful.

Where could you enhance your code? How would these improvements make your code more efficient, secure, and so on?
Some of these methods are definitely at a less-than-ideal time complexity. I know in one method in particular, I'm doing nested iteration.
The way that I'm handling the dat file could also be improved by adjusting when exactly the file is opened and close.
I believe if I were to do this project again I would make accessing the dat it's own method that is called when needed.

Which pieces of the code did you find most challenging to write, and how did you overcome this? What tools or resources are you adding to your support network?
In all honesty, the most frustrating part of this project was getting VS set up to handle Python. The problem was local, of course.
Whereas most guides I found online were 32x, my install was 64x, and my folder hierarchy was changed because of this.
There also seems to be quite a bit of redundancy in the folders.

What skills from this project will be particularly transferable to other projects or course work?
Again, multiple language integration within VS, and outside. The knowledge of when or why to use multiple languages.

How did you make this program maintainable, readable, and adaptable?
Comments at every point that something new is implemented, in an easily understandable line-by-line explanation.
The methods are broken up cleanly, and it should be easy to understand what the intended purpose of each thing is, and how to modify the code.
