/*=auto=========================================================================

  Portions (c) Copyright 2005 Brigham and Women's Hospital (BWH) All Rights Reserved.

  See Doc/copyright/copyright.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Program:   3D Slicer
  Module:    $RCSfile: vtkMRMLHierarchyNode.h,v $
  Date:      $Date: 2006/03/19 17:12:29 $
  Version:   $Revision: 1.13 $

=========================================================================auto=*/
///  vtkMRMLHierarchyNode - abstract class representing a hierarchy member

#ifndef __vtkMRMLHierarchyNode_h
#define __vtkMRMLHierarchyNode_h


#include "vtkMRML.h"
#include "vtkMRMLScene.h"
#include "vtkMRMLNode.h"


class VTK_MRML_EXPORT vtkMRMLHierarchyNode : public vtkMRMLNode
{
  public:
  static vtkMRMLHierarchyNode *New(){return NULL;};
  vtkTypeMacro(vtkMRMLHierarchyNode,vtkMRMLNode);
  void PrintSelf(ostream& os, vtkIndent indent);

  virtual vtkMRMLNode* CreateNodeInstance() = 0;

  /// 
  /// Read node attributes from XML file
  virtual void ReadXMLAttributes( const char** atts);

  /// 
  /// Write this node's information to a MRML file in XML format.
  virtual void WriteXML(ostream& of, int indent);

  /// 
  /// Copy the node's attributes to this object
  virtual void Copy(vtkMRMLNode *node);

  /// 
  /// Get node XML tag name (like Volume, Model)
  virtual const char* GetNodeTagName() = 0;

  /// 
  /// Updates this node if it depends on other nodes 
  /// when the node is deleted in the scene
  virtual void UpdateReferences();

  /// 
  /// Observe the reference transform node
  virtual void UpdateScene(vtkMRMLScene *scene);

  /// 
  /// Update the stored reference to another node in the scene
  virtual void UpdateReferenceID(const char *oldID, const char *newID);

  /// 
  /// Associated prent MRML node
  vtkMRMLHierarchyNode* GetParentNode();

  /// 
  /// Get the top parent node in the hierarchy
  vtkMRMLHierarchyNode* GetTopParentNode();

  /// 
  /// String ID of the parent hierarchy MRML node
  virtual char* GetParentNodeID()
  {
    return GetParentNodeIDReference();
  }

  virtual void SetParentNodeID(const char* ref);

//BTX
  /// 
  /// Given this hierarchy node returns all it's children recursively. 
  void GetAllChildrenNodes(std::vector< vtkMRMLHierarchyNode *> &childrenNodes);

  /// 
  /// Given this hierarchy node returns all it's 1st level children (not recursive). 
  /// Note: Most compilers don't make a copy of the list if you call the function like that:
  /// std::vector< vtkMRMLModelHierarchyNode > children = this->GetHierarchyChildrenNodes(parent);
  std::vector< vtkMRMLHierarchyNode *> GetChildrenNodes();
//ETX

  /// Returns the number of immediate children in the hierarchy
  int GetNumberOfChildrenNodes()
  {
    return this->GetChildrenNodes().size();
  }

  /// Get n-th child node sorted in the order of their SortingValue
  vtkMRMLHierarchyNode *GetNthChildNode(int index);

  /// Get index of this node in it's parent based on the value of their SortingValue
  int GetIndexInParent();

  /// Set index of this node in it's parent based on the value of their SortingValue
  void SetIndexInParent(int index);

  /// Removes immediate children nodes, their children are reparented to this parent node.
  void RemoveHierarchyChildrenNodes();

  /// Removes all children hierarchy nodes including children of childern, etc.
  void RemoveAllHierarchyChildrenNodes();

  /// 
  /// Node's Sorting Value
  vtkSetMacro(SortingValue, double);
  vtkGetMacro(SortingValue, double);

protected:
  vtkMRMLHierarchyNode();
  ~vtkMRMLHierarchyNode();
  vtkMRMLHierarchyNode(const vtkMRMLHierarchyNode&);
  void operator=(const vtkMRMLHierarchyNode&);

  /// 
  /// String ID of the parent hierarchy MRML node
  vtkSetReferenceStringMacro(ParentNodeIDReference);
  vtkGetStringMacro(ParentNodeIDReference);

  char *ParentNodeIDReference;

  /// Mark hierarchy as modified when you
  static void HierarchyIsModified(vtkMRMLScene *scene);

  //BTX
  typedef std::map<std::string, std::vector< vtkMRMLHierarchyNode *> > HierarchyChildrenNodesType;

  static std::map< vtkMRMLScene*, HierarchyChildrenNodesType> SceneHierarchyChildrenNodes;
  static std::map< vtkMRMLScene*, unsigned long> SceneHierarchyChildrenNodesMTime;
  //ETX
  
  double SortingValue;

  static double MaximumSortingValue;

  void UpdateChildrenMap();

};

#endif


 

