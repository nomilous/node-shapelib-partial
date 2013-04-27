require('nez').realize 'ShapeFile', (ShapeFile, test, it) -> 

    it 'loads a shape file', (done) -> 

        shapeFile = new ShapeFile
        shapeFile.open './sample/ne_110m_land', (error, shapeData) ->

            shapeData.count.should.equal 127
            shapeData.type.should.equal 5
            shapeData.shapes[126].fields.featurecla.should.equal 'Country'
            shapeData.shapes[126].vertexCount.should.equal 132
            shapeData.shapes[126].vertices[131][0].should.equal -27.10045999999997
            shapeData.shapes[126].vertices[131][1].should.equal 83.51966000000004
            test done

    it 'errors', (done) -> 

        (new ShapeFile).open 'missing', (error, shapeData) -> 

            error.should.match /Unable to open shape file/
            test done
