/*
  Copyright (c) 2004-2011 The FlameRobin Development Team

  Permission is hereby granted, free of charge, to any person obtaining
  a copy of this software and associated documentation files (the
  "Software"), to deal in the Software without restriction, including
  without limitation the rights to use, copy, modify, merge, publish,
  distribute, sublicense, and/or sell copies of the Software, and to
  permit persons to whom the Software is furnished to do so, subject to
  the following conditions:

  The above copyright notice and this permission notice shall be included
  in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


  $Id$

*/
//-----------------------------------------------------------------------------
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <wx/dir.h>
#include <wx/menu.h>

#include "config/Config.h"
#include "gui/CommandIds.h"
#include "gui/ContextMenuMetadataItemVisitor.h"
#include "metadata/column.h"
#include "metadata/domain.h"
#include "metadata/database.h"
#include "metadata/exception.h"
#include "metadata/function.h"
#include "metadata/generator.h"
#include "metadata/MetadataTemplateManager.h"
#include "metadata/procedure.h"
#include "metadata/role.h"
#include "metadata/root.h"
#include "metadata/server.h"
#include "metadata/table.h"
#include "metadata/trigger.h"
#include "metadata/view.h"

//-----------------------------------------------------------------------------
ContextMenuMetadataItemVisitor::ContextMenuMetadataItemVisitor(wxMenu* menu)
    : MetadataItemVisitor(), menuM(menu)
{
}
//-----------------------------------------------------------------------------
ContextMenuMetadataItemVisitor::~ContextMenuMetadataItemVisitor()
{
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::visitColumn(Column& column)
{
    addGenerateCodeMenu(column);
    if (!column.isSystem())
    {
        addSeparator();
        addDropItem(column);
        addSeparator();
        // TODO: addRefreshItem();
        addPropertiesItem();
    }
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::visitDatabase(Database& database)
{
    menuM->Append(Cmds::Menu_Connect, _("&Connect"));
    menuM->Append(Cmds::Menu_ConnectAs, _("Connect &as..."));
    menuM->Append(Cmds::Menu_Disconnect, _("&Disconnect"));
    menuM->Append(Cmds::Menu_Reconnect, _("Reconnec&t"));
    addSeparator();
    menuM->Append(Cmds::Menu_ExecuteStatements, _("Execute &SQL statements"));
    addSeparator();

    wxMenu* toolsMenu = new wxMenu();
    menuM->Append(0, _("&Tools"), toolsMenu);
    // Tools submenu
    toolsMenu->Append(Cmds::Menu_Backup, _("&Backup database"));
    toolsMenu->Append(Cmds::Menu_Restore, _("Rest&ore database"));
    addSeparator();
    toolsMenu->Append(Cmds::Menu_RecreateDatabase, _("Recreate empty database"));
    addSeparator();
    addGenerateCodeMenu(database, toolsMenu);
    toolsMenu->Append(Cmds::Menu_MonitorEvents, _("&Monitor events"));
    toolsMenu->Append(Cmds::Menu_GenerateData, _("&Test data generator"));

    menuM->Append(Cmds::Menu_DropDatabase, _("Dr&op database"));
    addSeparator();
    menuM->Append(Cmds::Menu_DatabaseRegistrationInfo,
        _("Database registration &info"));
    menuM->Append(Cmds::Menu_UnRegisterDatabase, _("&Unregister database"));
    menuM->Append(Cmds::Menu_DatabasePreferences,
        _("Database &preferences"));
    addSeparator();
    addRefreshItem();
    menuM->Append(Cmds::Menu_DatabaseProperties, _("P&roperties"));
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::visitDomain(Domain& domain)
{
    addAlterItem(domain);
    addDropItem(domain);
    addSeparator();
    addGenerateCodeMenu(domain);
    addSeparator();
    addRefreshItem();
    addPropertiesItem();
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::visitDomains(Domains& domains)
{
    addCreateItem();
    addSeparator();
    addGenerateCodeMenu(domains);
    addSeparator();
    addRefreshItem();
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::visitException(Exception& exception)
{
    addDropItem(exception);
    addSeparator();
    addGenerateCodeMenu(exception);
    addSeparator();
    addRefreshItem();
    addPropertiesItem();
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::visitExceptions(Exceptions& exceptions)
{
    addCreateItem();
    addSeparator();
    addGenerateCodeMenu(exceptions);
    addSeparator();
    addRefreshItem();
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::visitFunction(Function& function)
{
    addDropItem(function);
    addSeparator();
    addGenerateCodeMenu(function);
    addSeparator();
    addRefreshItem();
    addPropertiesItem();
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::visitFunctions(Functions& functions)
{
    menuM->Append(Cmds::Menu_CreateObject, _("Declare &new"));
    addSeparator();
    addGenerateCodeMenu(functions);
    addSeparator();
    addRefreshItem();
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::visitGenerator(Generator& generator)
{
    menuM->Append(Cmds::Menu_ShowGeneratorValue, _("Show &value"));
    menuM->Append(Cmds::Menu_SetGeneratorValue, _("&Set value"));
    addSeparator();
    addDropItem(generator);
    addSeparator();
    addGenerateCodeMenu(generator);
    addSeparator();
    addRefreshItem();
    addPropertiesItem();
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::visitGenerators(Generators& generators)
{
    menuM->Append(Cmds::Menu_ShowAllGeneratorValues, _("Show &all values"));
    addSeparator();
    addCreateItem();
    addSeparator();
    addGenerateCodeMenu(generators);
    addSeparator();
    addRefreshItem();
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::visitProcedure(Procedure& procedure)
{
    menuM->Append(Cmds::Menu_ExecuteProcedure, _("&Execute"));
    addShowColumnsItem();
    addAlterItem(procedure);
    addDropItem(procedure);
    addSeparator();
    addGenerateCodeMenu(procedure);
    addSeparator();
    // TODO: addRefreshItem();
    addPropertiesItem();
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::visitProcedures(Procedures& procedures)
{
    addCreateItem();
    addSeparator();
    addGenerateCodeMenu(procedures);
    addSeparator();
    addRefreshItem();
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::visitRole(Role& role)
{
    addDropItem(role);
    addSeparator();
    addGenerateCodeMenu(role);
    addSeparator();
    // TODO: addRefreshItem();
    addPropertiesItem();
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::visitRoles(Roles& roles)
{
    addCreateItem();
    addSeparator();
    addGenerateCodeMenu(roles);
    addSeparator();
    addRefreshItem();
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::visitSysRoles(SysRoles& sysRoles)
{
    addGenerateCodeMenu(sysRoles);
    addSeparator();
    addRefreshItem();
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::visitRoot(Root& root)
{
    menuM->Append(Cmds::Menu_RegisterServer, _("&Register server"));
    addSeparator();
    addGenerateCodeMenu(root);
    addSeparator();
    menuM->Append(wxID_ABOUT, _("&About FlameRobin"));
    menuM->Append(wxID_PREFERENCES, _("&Preferences"));
    addSeparator();
    menuM->Append(wxID_EXIT, _("&Quit"));
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::visitServer(Server& server)
{
    menuM->Append(Cmds::Menu_RegisterDatabase, 
        _("&Register existing database"));
    menuM->Append(Cmds::Menu_CreateDatabase, _("Create &new database"));
    menuM->Append(Cmds::Menu_RestoreIntoNew,
        _("Restore bac&kup into new database"));
    addSeparator();
    addGenerateCodeMenu(server);
    addSeparator();
    menuM->Append(Cmds::Menu_GetServerVersion, _("Retrieve server &version"));
    menuM->Append(Cmds::Menu_ManageUsers, _("&Manage users"));
    addSeparator();
    menuM->Append(Cmds::Menu_UnRegisterServer, _("&Unregister server"));
    menuM->Append(Cmds::Menu_ServerProperties,
        _("Server registration &info"));
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::visitTable(Table& table)
{
    addBrowseDataItem();
    addGenerateCodeMenu(table);
    addSeparator();
    if (!table.isSystem())
        menuM->Append(Cmds::Menu_AddColumn, _("&Add column"));
    addShowColumnsItem();
    if (!table.isSystem())
    {
        menuM->Append(Cmds::Menu_CreateTriggerForTable, 
        _("Create new &trigger"));
    }
    addDropItem(table);
    addSeparator();
    // TODO: addRefreshItem();
    addPropertiesItem();
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::visitTables(Tables& tables)
{
    addCreateItem();
    addSeparator();
    addGenerateCodeMenu(tables);
    addSeparator();
    addRefreshItem();
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::visitSysTables(SysTables& sysTables)
{
    addGenerateCodeMenu(sysTables);
    addSeparator();
    addRefreshItem();
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::visitTrigger(Trigger& trigger)
{
    addGenerateCodeMenu(trigger);
    addSeparator();
    addAlterItem(trigger);
    addDropItem(trigger);
    addSeparator();
    addGenerateCodeMenu(trigger);
    addSeparator();
    // TODO: addRefreshItem();
    addPropertiesItem();
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::visitTriggers(Triggers& triggers)
{
    addCreateItem();
    addSeparator();
    addGenerateCodeMenu(triggers);
    addSeparator();
    addRefreshItem();
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::visitView(View& view)
{
    addBrowseDataItem();
    addShowColumnsItem();
    addGenerateCodeMenu(view);
    addSeparator();
    addAlterItem(view);
    addDropItem(view);
    addSeparator();
    // TODO: addRefreshItem();
    addPropertiesItem();
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::visitViews(Views& views)
{
    addCreateItem();
    addSeparator();
    addGenerateCodeMenu(views);
    addSeparator();
    addRefreshItem();
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::addAlterItem(MetadataItem& metadataItem)
{
    if (!metadataItem.isSystem())
        menuM->Append(Cmds::Menu_AlterObject, _("&Alter"));
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::addCreateItem()
{
    menuM->Append(Cmds::Menu_CreateObject, _("Create &new"));
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::addDropItem(MetadataItem& metadataItem)
{
    if (!metadataItem.isSystem())
        menuM->Append(Cmds::Menu_DropObject, _("Dr&op"));
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::addGenerateCodeMenu(
    MetadataItem& metadataItem, wxMenu* parent)
{
    MetadataTemplateManager tm(&metadataItem);
    if (tm.descriptorsBegin() == tm.descriptorsEnd())
        return;

    int i = (int)Cmds::Menu_TemplateFirst;
    wxMenu* templateMenu = new wxMenu();
    for (TemplateDescriptorList::const_iterator it = tm.descriptorsBegin();
        it != tm.descriptorsEnd(); ++it, ++i)
    {
        templateMenu->Append(i, (*it)->getMenuCaption());
    }
    if (!parent)
        parent = menuM;
    parent->Append(Cmds::Menu_TemplateFirst, _("&Generate code"), templateMenu);
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::addPropertiesItem()
{
    menuM->Append(Cmds::Menu_ObjectProperties, _("P&roperties"));
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::addRefreshItem()
{
    menuM->Append(Cmds::Menu_ObjectRefresh, _("Re&fresh"));
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::addBrowseDataItem()
{
    menuM->Append(Cmds::Menu_BrowseColumns, _("Brow&se data"));
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::addShowColumnsItem()
{
    if (config().get(wxT("ShowColumnsInTree"), true))
        menuM->Append(Cmds::Menu_LoadColumnsInfo, _("Show columns in&fo"));
}
//-----------------------------------------------------------------------------
void ContextMenuMetadataItemVisitor::addSeparator()
{
    size_t count = menuM->GetMenuItemCount();
    if (count > 0 && !menuM->FindItemByPosition(count - 1)->IsSeparator())
        menuM->AppendSeparator();
}
//-----------------------------------------------------------------------------
