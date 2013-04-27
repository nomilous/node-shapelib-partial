require('nez').realize 'Index', (Index, test, it, should) -> 

    it 'exports ShapeFile', (done) -> 

        should.exist Index.ShapeFile
        test done
