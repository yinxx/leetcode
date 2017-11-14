"""

Designing an in-memory file system:

Basically, we are creating a directory tree, with the root being "/".
We need to support these 4 functionalities:

1. ls: return list of files/directory names in current directory.
2. mkdir: Create (potentially nested) directories that dont exist.
3. addContentToFile: Either create the file with content, or append to existing.
4. readContentFromFile: Given file path return content.

This implementation will pretty much be a trie. We can represent Tries in python as:
node = { file/directory name : ""/{} }

"""

class FileSystem(object):
    def __init__(self):
        self.root = {} 

    def parse_path(self, path):
        """
        Helper method to find the path.
        :type path: str
        :rtype: List[str]
        """
        path = path.split('/')[1:]
        if not path[0]:
            path = path[1:]
        if not path[-1]:
            path = path[:-1]
        return path

    def traverse_path(self, path):
        """
        Helper method to traverse to a specific path.
        If the path doesn't exist, then create it.
        :type path: List[str]
        :rtype: dict
        """
        n = self.root
        for p in path:
            if p not in n:
                n[p] = {} 
            n = n[p]
        return n

    def ls(self, path):
        """
        :type path: str
        :rtype: List[str]
        """
        path = self.parse_path(path)
        # ls could be pointing to a file
        if path:
            n = self.traverse_path(path[:-1]) 
            name = path[-1]
            try:
                return sorted(n[name].keys())
            except:
                return [name]
        else:
            return sorted(self.root.keys())

    def mkdir(self, path):
        """
        :type path: str
        :rtype: void
        """
        self.traverse_path(self.parse_path(path))

    def addContentToFile(self, path, content):
        """
        :type filePath: str
        :type content: str
        :rtype: void
        """
        path = self.parse_path(path)
        n = self.traverse_path(path[:-1])
        if path[-1] not in n:
            n[path[-1]] = ""
        n[path[-1]] += content

    def readContentFromFile(self, path):
        """
        :type filePath: str
        :rtype: str
        """
        path = self.parse_path(path)
        n = self.traverse_path(path[:-1])
        return n[path[-1]]
