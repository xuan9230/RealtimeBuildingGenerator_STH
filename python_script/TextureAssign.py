import bpy

def isBetween(a,num1,num2):
    if a>=num1 and a<num2:
        return True
    else:
        return False


def SinglePic(fpath,objName,imgName,texSeq):
    #import obj
    bpy.ops.import_scene.obj(filepath='f:\\testData\\'+objName+'.obj')
    # new material and texture
    bpy.ops.material.new()
    bpy.data.materials[texSeq].name = 'mat'+objName
    bpy.ops.texture.new()
    bpy.data.textures[texSeq].name = 'tex'+objName
    bpy.data.textures['tex'+objName].type = 'IMAGE'
    # assign texture
    bpy.ops.image.open(filepath = fpath+imgName)
    npName = objName+'_'+imgName
    bpy.data.images[imgName].name = npName
    bpy.data.textures['tex'+objName].image = bpy.data.images[npName]
    bpy.data.materials['mat'+objName].active_texture = bpy.data.textures['tex'+objName]
    bpy.data.objects[objName].active_material = bpy.data.materials['mat'+objName]

    

def MultiPic(fpath,objName,imgName,texSeq):
    fp = open('f:\\testData\\'+objName+'_1.obj')
    fp.readline()
    fp.readline()
    mul = fp.readline()
    fp.close()
    mul = mul.strip('\n')
    mul = int(mul)
    bpy.ops.image.open(filepath = fpath+imgName)
    npName = objName+'_'+imgName
    bpy.data.images[imgName].name = npName
    bpy.ops.material.new()
    bpy.data.materials[texSeq].name = 'mat'+objName
    bpy.ops.texture.new()
    bpy.data.textures[texSeq].name = 'tex'+objName
    bpy.data.textures['tex'+objName].type = 'IMAGE'
    bpy.data.textures['tex'+objName].image = bpy.data.images[npName]
    bpy.data.materials['mat'+objName].active_texture = bpy.data.textures['tex'+objName]
    for i in range(1,mul+1):
        obSName = objName+'_'+str(i)
        bpy.ops.import_scene.obj(filepath='f:\\testData\\'+obSName+'.obj')
        bpy.data.objects[obSName].active_material = bpy.data.materials['mat'+objName]
        

def TextureAssign(objName,texSeq,att,imgName):    
    # choose texture
    if att == 0:
        bpy.ops.import_scene.obj(filepath='f:\\testData\\'+objName+'.obj')
    elif att == 6:
        fpath = 'f:\\RBG\\components\\textures\\Window\\'
        MultiPic(fpath,objName,imgName,texSeq)
    elif att == 7:
        fpath = 'f:\\RBG\\components\\textures\\Ornament\\'
        MultiPic(fpath,objName,imgName,texSeq)
    elif att == 8:
        fpath = 'f:\\RBG\\components\\textures\\Door\\'
        SinglePic(fpath,objName,imgName,texSeq)
    elif att == 9:
        fpath = 'f:\\RBG\\components\\textures\\Window\\'
        MultiPic(fpath,objName,imgName,texSeq)
    elif att == 10:
        fpath = 'f:\\RBG\\components\\textures\\Ornament\\'
        MultiPic(fpath,objName,imgName,texSeq)
    elif att == 11:
        fpath = 'f:\\RBG\\components\\textures\\Facade\\'
        SinglePic(fpath,objName,imgName,texSeq)
    elif att == 14:
        fpath = 'f:\\RBG\\components\\textures\\Bands\\'
        SinglePic(fpath,objName,imgName,texSeq)
    elif att == 15:
        fpath = 'f:\\RBG\\components\\textures\\Pilaster\\'
        MultiPic(fpath,objName,imgName,texSeq)
    elif att == 16:
        fpath = 'f:\\RBG\\components\\textures\\Quoin\\'
        SinglePic(fpath,objName,imgName,texSeq)
                
    
def BuildingTexture():
    fp = open('f:\\testData\\att0.obj')
    att = fp.readline()
    sty = fp.readline()
    fp.close()
    sty = sty.strip('\n')
    sty = int(sty)
    if isBetween(sty,0,20):
        imgName = '1.jpg'
        GnImg = '2.jpg'
    elif isBetween(sty,20,40):
        imgName = '2.jpg'
        GnImg = '3.jpg'
    elif isBetween(sty,40,60):
        imgName = '3.jpg'
        GnImg = '4.jpg'
    elif isBetween(sty,60,80):
        imgName = '4.jpg'
        GnImg = '5.jpg'
    elif isBetween(sty,80,100):
        imgName = '5.jpg'
        GnImg = '1.jpg'    
    TextureAssign('att0',0,0,imgName)
    TextureAssign('att6',0,6,imgName)
    TextureAssign('att7',1,7,imgName)
    TextureAssign('att8',2,8,imgName)
    TextureAssign('att9',3,9,GnImg)
    TextureAssign('att10',4,10,GnImg)
    TextureAssign('att11',5,11,imgName)
    TextureAssign('att14',6,14,imgName)
    if sty>80:
        TextureAssign('att15',7,15,imgName)
    else:
        TextureAssign('att16',7,16,imgName)
    bpy.ops.export_scene.autodesk_3ds(filepath='f:\\testData\\result\\Building3ds.3ds')
    bpy.ops.export_scene.obj(filepath='f:\\testData\\result\\BuildingObj.obj')
    bpy.ops.export_scene.fbx(filepath='f:\\testData\\result\\BuildingFbx.fbx')


BuildingTexture()
